#include <cstdio>
#include <algorithm>

const int MAXN = 400010;
typedef long long ll;

int n, adj[MAXN], to[MAXN], next[MAXN];
ll cost[MAXN];
inline void add_edge(int u, int v, ll w, int e) {
    to[e] = v;
    cost[e] = w;
    next[e] = adj[u];
    adj[u] = e;
}
int dl[MAXN], ua, ub;
ll d[MAXN], diam;
bool vis[MAXN];
inline void dfs(int u) {
    vis[u] = true;
    d[u] = 0;
    dl[u] = u;
    int e, v, sd = 0;
    ll sc = 0, vc, len;
    for (e = adj[u]; e; e = next[e]) {
        v = to[e];
        if (!vis[v]) {
            dfs(v);
            vc = d[v] + cost[e];
            if (vc >= d[u])
                sc = d[u], d[u] = vc, sd = dl[u], dl[u] = dl[v];
            else if (vc > sc)
                sc = vc, sd = dl[v];
        }
    }
    // if (d[u] == 0)
    //     dl[u] = u;
    len = d[u] + sc;
    if (len > diam)
        diam = len, ua = dl[u], ub = sd;
}
ll depth1[MAXN], depth2[MAXN], *depth;
inline void dfs1(int u, ll deep) {
    vis[u] = true;
    depth[u] = deep;
    int e, v;
    for (e = adj[u]; e; e = next[e]) {
        v = to[e];
        if (!vis[v])
            dfs1(v, deep + cost[e]);
    }
}/*
bool indiam[MAXN];
inline bool dfs2(int u) {
    vis[u] = true;
    if (u == ua || u == ub) {
        indiam[u] = true;
        return false;
    }
    int e, v;
    for (e = adj[u]; e; e = next[e]) {
        v = to[e];
        if (!vis[v]) {
            if (dfs2(v))
                return false;
            if (indiam[v]) {
                if (indiam[u])
                    return true;
                indiam[u] = true;
            }
        }
    }
    return false;
}*/
int main() {
    int i, u, v;
    ll w, ans = 0;
    scanf("%d%d", &n, &i);
    for (i = 1; i < n; ++i) {
        scanf("%d%d%lld", &u, &v, &w);
        add_edge(u, v, w, i);
        add_edge(v, u, w, n + i - 1);
    }
    dfs(1);
    std::fill(vis + 1, vis + n + 1, false);
    depth = depth1;
    dfs1(ua, 0);
    std::fill(vis + 1, vis + n + 1, false);
    depth = depth2;
    dfs1(ub, 0);
    /*
    std::fill(vis + 1, vis + n + 1, false);
    for (u = 1; u == ua || u == ub; ++u);
    dfs2(u);*/
    for (i = 1; i <= n; ++i) {
        ans = std::max(ans, diam + std::min(depth1[i], depth2[i]));
    }
    printf("%lld\n", ans);

    return 0;
}
