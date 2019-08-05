#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAXN = 10005, MAXM = 50005, INF = 0x7f7f7f7f;
int n, m;

int fa[MAXN];
void uf_init() {
    for (int i = 1; i <= n; ++i)
        fa[i] = i;
}
int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
inline void unite(int u, int v) {
    fa[find(u)] = find(v);
}
inline bool same(int u, int v) {
    return find(u) == find(v);
}
struct Kru {
    int u, v, w;
} kse[MAXM];
inline bool cmp(const int a, const int b) {
    return kse[a].w > kse[b].w; // to find maximium spannning tree
}

struct Edge {
    int v, w;
    Edge *next;
} se[MAXM << 1], *adj[MAXN];
int ecnt;
inline void arc(int u, int v, int w) {
    Edge &e = se[++ecnt];
    e.v = v;
    e.w = w;
    e.next = adj[u];
    adj[u] = &e;
}
int dep[MAXN], rt[MAXN], jmp[MAXN][20], minw[MAXN][20], lbn, root;
void dfs(int u) {
    int v;
    dep[u] = dep[jmp[u][0]] + 1;
    rt[u] = root;
    for (Edge *e = adj[u]; e; e = e->next) {
        v = e->v;
        if (!dep[v]) {
            jmp[v][0] = u;
            minw[v][0] = e->w;
            dfs(v);
        }
    }
}
int query(int u, int v) {
    static int j, res;
    if (rt[u] != rt[v])
        return INF;
    res = INF;
    if (dep[u] < dep[v])
        std::swap(u, v);
    for (j = lbn; j >= 0; --j)
        if (dep[jmp[u][j]] >= dep[v]) {
            res = std::min(res, minw[u][j]);
            u = jmp[u][j];
        }
    if (u == v)
        return res;
    for (j = lbn; j >= 0; --j)
        if (jmp[u][j] != jmp[v][j]) {
            res = std::min(res, std::min(minw[u][j], minw[v][j]));
            u = jmp[u][j];
            v = jmp[v][j];
        }
    res = std::min(res, std::min(minw[u][0], minw[v][0]));
    return res;

}
void init() {
    static int i, j, kind[MAXM];
    for (i = 1; i <= m; ++i)
        kind[i] = i;
    std::sort(kind + 1, kind + m + 1, cmp);
    uf_init(); // **
    for (i = 1; i <= m; ++i) {
        Kru &e = kse[kind[i]];
        if (!same(e.u, e.v))
            unite(e.u, e.v), arc(e.u, e.v, e.w), arc(e.v, e.u, e.w);
    }
    memset(minw, 0x7f, sizeof(minw));
    for (i = 1; i <= n; ++i)
        if (!dep[i])
            root = i, dfs(i); // could be a forest
    for (j = 1; (1 << j) <= n; ++j)
        for (i = 1; i <= n; ++i) 
            if (jmp[i][j - 1]) { 
                jmp[i][j] = jmp[jmp[i][j - 1]][j - 1];
                minw[i][j] = std::min(minw[i][j - 1], minw[jmp[i][j - 1]][j - 1]);
            }
    lbn = j - 1;
}
int main() {
    static int i, q, u, v, ret;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; ++i) {
        Kru &e = kse[i];
        scanf("%d%d%d", &e.u, &e.v, &e.w);
    }
    init();
    scanf("%d", &q);
    for (i = 1; i <= q; ++i) {
        scanf("%d%d", &u, &v);
        ret = query(u, v);
        printf("%d\n", ret == INF ? -1 : ret);
    }

    return 0;
}
