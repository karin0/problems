#include <cstdio>
#include <stack>

const int MAXV = 100005, MAXE = 300005;

int cv, ce;
struct Edge {
    int u, v;
    Edge *next;
} se[MAXE];
Edge *adj[MAXV], *sse[MAXE];

inline void arc(int u, int v, int e) {
    se[e].u = u;
    se[e].v = v;
    se[e].next = adj[u];
    adj[u] = se + e;
}
int belong[MAXV], siz[MAXV], scnt, ssecnt, dfn[MAXV];
void dfs(int u) {
    static std::stack<int> sta;
    static bool ins[MAXV];
    static int low[MAXV], tim;
    dfn[u] = ++tim;
    low[u] = tim;
    sta.push(u);
    ins[u] = true;
    int v;
    for (Edge *e = adj[u]; e; e = e->next) {
        v = e->v;
        if (!dfn[v])
            dfs(v), low[u] = std::min(low[u], low[v]);
        else if (ins[v])
            low[u] = std::min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
        ++scnt;
        do {
            v = sta.top();
            sta.pop();
            ins[v] = false;
            belong[v] = scnt;
            ++siz[scnt];
        } while (u != v);
    }
}

bool spe[MAXV];
int ind[MAXV], oud[MAXV];
int main() {
    int i, u, v, cnt = 0;
    scanf("%d%d", &cv, &ce);
    for (i = 1; i <= ce; ++i)
        scanf("%d%d", &u, &v), arc(u, v, i);
    for (u = 1; u <= cv; ++u) // ****
        if (!dfn[u])
            dfs(u);
    for (Edge *e = se + 1; e <= se + ce; ++e)
        if (belong[e->u] != belong[e->v])
            ++ind[belong[e->v]], sse[++ssecnt] = e; // printf("[%d]\n", e->u);
    for (i = 1; i <= ssecnt; ++i) {
        Edge *e = sse[i];
        if (ind[belong[e->v]] <= 1 && siz[belong[e->u]] == 1)
            spe[belong[e->u]] = true; // printf("[%d]\n", e->u);
    }
    for (u = 1; u <= scnt; ++u)
        if (ind[u] == 0)
            ++cnt;
    for (u = 1; u <= scnt; ++u)
        if (ind[u] == 0 && siz[u] == 1 && !spe[u]) {
            --cnt;
            break;
        }
    printf("%.6lf\n", (double)(cv - cnt) / cv);
    
    return 0;
}
