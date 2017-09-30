#include <cstdio>
#include <cmath>
#include <algorithm>

const int MAXN = 200010, MAXB = 20;
int n, adj[MAXN], to[MAXN * 2], next[MAXN * 2];
inline void arc(int u, int v, int e) {
    to[e] = v;
    next[e] = adj[u];
    adj[u] = e;
}

int jmp[MAXN][MAXB], depth[MAXN], mj;
bool vis[MAXN];
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
inline int lca(int u, int v) {
    static int j;
    if (u == v)
        return u;
    if (depth[u] < depth[v])
        std::swap(u, v);
    for (j = mj; j >= 0; --j)
        if (depth[jmp[u][j]] >= depth[v])
            u = jmp[u][j];
    if (u == v)
        return u;
    for (j = mj; j >= 0; --j)
        if (jmp[u][j] != jmp[v][j])
            u = jmp[u][j], v = jmp[v][j];
    return jmp[u][0];
}
inline void init() {
    mj = ceil(log2(n));
    dfs(1, 1);
    for (int j = 1; j <= mj; ++j)
        for (int i = 1; i <= n; ++i)
            jmp[i][j] = jmp[jmp[i][j - 1]][j - 1];
    // for (int j = 0; j <= mj; ++j)
}

int main() {
    int m, rid, i, x, u, v, w, luv, lwv, pos, ans;
    scanf("%d%d%d", &n, &m, &rid);
    for (i = 1; i < n; ++i)
        scanf("%d%d", &u, &v), arc(u, v, i), arc(v, u, n - 1 + i);
    init();
    for (i = 1; i <= m; ++i) {
        scanf("%d%d%d", &u, &v, &w);
        if (depth[u] > depth[w])
            std::swap(u, w);
        if (u == w) {
            printf("%d\n", 1 + depth[v] + depth[u] - 2 * depth[lca(u, v)]);
        } else {
            x = lca(u, w);
            if (rid >= 5 && rid <= 10) {
                pos = u;
                ans = depth[x] + depth[v] - 2 * depth[lca(x, v)];
                while (pos != x) {
                    ans = std::min(ans, depth[pos] + depth[v] - 2 * depth[lca(pos, v)]);
                    pos = jmp[pos][0];
                }
                pos = w;
                while (pos != x) {
                    ans = std::min(ans, depth[pos] + depth[v] - 2 * depth[lca(pos, v)]);
                    pos = jmp[pos][0];
                }
                printf("%d\n", ans + 1);
                continue;
            }
            luv = lca(u, v);
            lwv = lca(w, v);
            if (x == u) {
                if (luv == u && lwv == w)
                    printf("%d\n", 1 + depth[v] - depth[w]);
                else if (luv == u && lwv == v)
                    printf("%d\n", 1);
                else {
                    if (lca(lwv, u) == u)
                        printf("%d\n", 1 + depth[v] - depth[lwv]);
                    else
                        printf("%d\n", 1 + depth[u] + depth[v] - 2 * depth[luv]);
                }
            } else if (luv == v || lwv == v) {
                if (depth[v] < depth[x])
                    printf("%d\n", 1 + depth[x] - depth[v]);
                else
                    printf("%d\n", 1);
            } else if (luv == u) {
                printf("%d\n", 1 + depth[v] - depth[u]);
            } else if (lwv == w) {
                printf("%d\n", 1 + depth[v] - depth[w]);
            } else
                printf("%d\n", 1 + depth[v] - std::max(depth[luv], depth[lwv]));
        }
    }

    return 0;
}
