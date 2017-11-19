// 倍增注意 MAXB 数组开大，否则会调一晚上
#include <cstdio>
#include <cmath>
#include <algorithm>

const int MAXN = 500010, MAXB = 29;
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
    int j;
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
    mj = floor(log2(n));
    dfs(1, 1);
    for (int j = 1; j <= mj; ++j)
        for (int i = 1; i <= n; ++i)
            jmp[i][j] = jmp[jmp[i][j - 1]][j - 1];
    // for (int j = 0; j <= mj; ++j)
}
int t;
inline int dis(int u, int v) {
    t = lca(u, v);
    return depth[u] + depth[v] - 2 * depth[t];
}

int main() {
    int m, i, u, v, w, x, y, z, vx, vy, vz, c, ans, l;
    scanf("%d%d", &n, &m);
    for (i = 1; i < n; ++i)
        scanf("%d%d", &u, &v), arc(u, v, i), arc(v, u, n - 1 + i);
    init();
    for (i = 1; i <= m; ++i) {
        scanf("%d%d%d", &u, &v, &w);
        c = dis(u, v);
        ans = t;
        c += dis(w, ans);
        l = dis(u, w);
        x = t;
        l += dis(v, x);
        if (l < c)
            c = l, ans = x;
        l = dis(v, w);
        x = t;
        l += dis(u, x);
        if (l < c)
            c = l, ans = x;
        printf("%d %d\n", ans, c);
    }

    return 0;
}
