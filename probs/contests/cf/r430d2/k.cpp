#include <cstdio>
#include <algorithm>

const int MAXV = 2e5 + 10, MAXE = 4e5 + 10;

int n, adj[MAXV], w[MAXV], to[MAXE], next[MAXE];
inline void add_edge(int u, int v, int e) {
    to[e] = v;
    next[e] = adj[u];
    adj[u] = e;
}

int ans[MAXV];
bool vis[MAXV];
inline void dfs(int u) {
    vis[u] = true;
    for (int e = adj[u], v; e; e = next[e]) {
        v = to[e];
        if (!vis[v]) {
            ans[v] = std::max(w[v], ans[u]);
            dfs(v);
        }
    }
}


char ch;
inline void read(int &res) {
    res = 0;
    ch = 0;
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9')
        res = res * 10 + ch - '0', ch = getchar();
}

int main() {
    int i, u, v;
    read(n);
    for (i = 1; i <= n; ++i) {
        read(w[i]);
    }
    for (i = 1; i < n; ++i) {
        read(u), read(v);
        add_edge(u, v, i);
        add_edge(v, u, n + i - 1);
    }
    ans[1] = w[1];
    dfs(1);
    for (i = 1; i <= n; ++i)
        printf("%d%c", ans[i], i == n ? '\n' : ' ');
    return 0;
}
