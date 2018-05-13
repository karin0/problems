#include <cstdio>
#include <algorithm>

const int MAXN = 100005, MAXM = 100005;
struct Edge {
    int v;
    Edge *next;
} se[MAXM << 1], *adj[MAXN];
int n, m, ecnt;
inline void arc(int u, int v) {
    Edge &e = se[++ecnt];
    e.v = v;
    e.next = adj[u];
    adj[u] = &e;
}
int dfn[MAXN], low[MAXN], tim;
bool cut[MAXN];
void dfs(int u, int fa) {
    dfn[u] = ++tim;
    low[u] = tim;
    int ch = 0, v;
    for (Edge *e = adj[u]; e; e = e->next) {
        v = e->v;
        if (!dfn[v]) {
            ++ch;
            dfs(v, u);
            low[u] = std::min(low[u], low[v]);
            if (low[v] >= dfn[u])
                cut[u] = true;
        } else if (dfn[v] < dfn[u] && v != fa)
            low[u] = std::min(low[u], dfn[v]);
    }
    if (fa == -1 && ch == 1)
        cut[u] = false;
}

int main() {
    static int i, u, v, cnt;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; ++i)
        scanf("%d%d", &u, &v), arc(u, v), arc(v, u);
    for (i = 1; i <= n; ++i)
        if (!dfn[i])
            dfs(i, -1);
    for (i = 1; i <= n; ++i)
        if (cut[i])
            ++cnt;
    printf("%d\n", cnt);
    for (i = 1; i <= n; ++i)
        if (cut[i])
            printf("%d ", i);
    putchar('\n');

    return 0;
}
