#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAXN = 500005, MAXM = 500005;
int n, m, ecnt;
struct Edge {
    int v, w;
    Edge *next;
} se[MAXM << 1], *adj[MAXN];
inline void arc(int u, int v) {
    Edge &e = se[++ecnt];
    e.v = v;
    e.next = adj[u];
    adj[u] = &e;
}
int dep[MAXN], jmp[MAXN][30], lbn, s;
void dfs(int u) {
    int v;
    dep[u] = dep[jmp[u][0]] + 1;
    for (Edge *e = adj[u]; e; e = e->next) {
        v = e->v;
        if (!dep[v]) {
            jmp[v][0] = u;
            dfs(v);
        }
    }
}
int lca(int u, int v) {
    static int j;
    if (dep[u] < dep[v])
        std::swap(u, v);
    for (j = lbn; j >= 0; --j)
        if (dep[jmp[u][j]] >= dep[v])
            u = jmp[u][j];
    if (u == v)
        return u;
    for (j = lbn; j >= 0; --j)
        if (jmp[u][j] != jmp[v][j])
            u = jmp[u][j], v = jmp[v][j];
    return jmp[u][0];

}
void init() {
    static int i, j;
    dfs(s);
    for (j = 1; (1 << j) <= n; ++j)
        for (i = 1; i <= n; ++i) 
            if (jmp[i][j - 1])
                jmp[i][j] = jmp[jmp[i][j - 1]][j - 1];
    lbn = j - 1;
}
int main() {
    static int i, u, v;
    scanf("%d%d%d", &n, &m, &s);
    for (i = 1; i < n; ++i) {
        scanf("%d%d", &u, &v);
        arc(u, v);
        arc(v, u);
    }
    init();
    for (i = 1; i <= m; ++i) {
        scanf("%d%d", &u, &v);
        printf("%d\n", lca(u, v));
    }

    return 0;
}
