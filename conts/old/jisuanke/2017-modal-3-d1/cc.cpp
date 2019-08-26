#include <cstdio>
#include <algorithm>

const int MAXN = 1e5 + 5, MAXB = 20;

int n, m, cv, ce;

struct Edge {
    int u, v, w;
    bool used;
} se[MAXN * 3];

namespace Tree {
    int adj[MAXN * 2], to[MAXN * 3], cost[MAXN * 3], next[MAXN * 3], depth[MAXN * 2], jmp[MAXN * 2][MAXB], ecnt;
    bool vis[MAXN * 2];
    
    inline void add_edge(int u, int v, int w) {
        to[++ecnt] = v;
        cost[ecnt] = w;
        next[ecnt] = adj[u];
        adj[u] = ecnt;
    }
    inline void lca_init() {
        for (int j = 1; j < MAXB; ++j)
            for (int i = 1; i <= cv; ++i)
                if (jmp[i][j - 1] > 0)
                    jmp[i][j] = jmp[jmp[i][j - 1]][j - 1];
    }
    inline int lca(int u, int v) {
        int b;
        if (depth[u] < depth[v])
            std::swap(u, v);
        for (b = MAXB - 1; b >= 0; --b)
            if (depth[jmp[u][b]] >= depth[v])
                u = jmp[u][b];
        if (u == v)
            return u;
        for (b = MAXB - 1; b >= 0; --b)
            if (jmp[u][b] != jmp[v][b])
                u = jmp[u][b], v = jmp[v][b];
        return jmp[u][0];
    }

    inline void dfs(int u, int deep) {
        vis[u] = true;
        depth[u] = deep;
        for (int e = adj[u], v; e; e = next[e]) {
            v = to[e];
            if (!vis[v]) {
                jmp[v][0] = u;
                dfs(v, deep + 1);
            }
        }
    }
    

}

namespace Kruskal {
    int fa[MAXN * 2];
    inline void init() {
        for (int i = 1; i <= n; ++i) {
            fa[i] = i;
            fa[n + i] = n + i;
        }
    }
    inline int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
    inline void merge(int x, int y) {
        fa[find(x)] = find(y);
    }
    inline bool same(int x, int y) {
        return find(x) == find(y);
    }
    
    inline bool cmp(const Edge &x, const Edge &y) {
        return x.w < y.w;
    }
    inline void kruskal() {
        std::sort(se + 1, se + m - 1, cmp);
        for (int i = 1; i <= m; ++i) {
            if (!same(se[i].u, se[i].v)) {
                merge(se[i].u, se[i].v);
                se[i].used = true;
                Tree::add_edge(se[i].u, se[i].v, se[i].w);
                Tree::add_edge(se[i].v, se[i].u, se[i].w);
            }
        }
    }
    
}
:
int main() {
    scanf("%d%d", &n, &m);


    return 0;
}
