#include <cstdio>
#include <algorithm>

const int MAXN = 200005;

int n, m, ans, adj[MAXN], to[MAXN * 2], next[MAXN * 2];
inline void add_edge(int u, int v, int e) {
    to[e] = v;
    next[e] = adj[u];
    adj[u] = e;
}

int diam, lca, fm[MAXN], fs[MAXN];
bool vis[MAXN], used[MAXN * 2];
inline int dfs(int u) {
    vis[u] = true;
    int e, v, dv, mv = 0, sv = 0, emv = 0, esv = 0, len;
    for (e = adj[u]; e; e = next[e]) {
        v = to[e];
        if (!vis[v]) {
            dv = dfs(v) + (used[e] ? -1 : 1);
            if (dv >= mv)
                sv = mv, mv = dv, esv = emv, emv = e; // ***
            else if (dv > sv)
                sv = dv, esv = e;
        }
    }
    fm[u] = emv, fs[u] = esv;
    len = mv + sv;
    if (len > diam)
        diam = len, lca = u;
    return mv;
}

inline void use(int e) {
    used[e] = true;
    if (e < n)
        used[e + n - 1] = true;
    else
        used[e - n + 1] = true;
}

int main() {
    int i, u, v, e;
    scanf("%d%d", &n, &m);
    for (i = 1; i < n; ++i) {
        scanf("%d%d", &u, &v);
        add_edge(u, v, i);
        add_edge(v, u, n - 1 + i);
    }
    dfs(1);
    // ans = 2 * (n - 1) - diam + 1;
    ans = n + n - diam - 1;
    if (m == 2) {
        for (e = fm[lca]; e; e = fm[to[e]])
            use(e);
        for (e = fs[lca]; e; e = fm[to[e]])
            use(e);
        std::fill(vis + 1, vis + n + 1, false);
        diam = -0x7f7f7f7f;
        dfs(1);
        ans = ans - diam + 1;
    }
    printf("%d\n", ans);

    return 0;
}
