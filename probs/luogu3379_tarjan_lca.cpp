#include <cstdio>
#include <vector>

const int MAXV = 5e5 + 5, MAXE = 1e6 + 10, MAXM = 5e5 + 5;

int n, adj[MAXV], to[MAXE], next[MAXE];
inline void add_edge(int u, int v, int e) {
    to[e] = v;
    next[e] = adj[u];
    adj[u] = e;
}

int pa[MAXV];
inline int find(int x) {
    return pa[x] == x ? x : pa[x] = find(pa[x]);
}

int root;
struct Query {
    int v, id;
};
int ans[MAXM];
std::vector<Query> query[MAXV];
bool vis[MAXV];
inline void tarjan(int u) {
    vis[u] = true;
    pa[u] = u;
    for (Query *q = &query[u].front(); q && q <= &query[u].back(); ++q)
        if (vis[q -> v] && !ans[q -> id])
            ans[q -> id] = find(q -> v);
    for (int e = adj[u], v; e; e = next[e]) {
        v = to[e];
        if (!vis[v]) {
            tarjan(v);
            pa[v] = u;
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
    int i, m, u, v;
    read(n), read(m), read(root);
    for (i = 1; i < n; ++i) {
        read(u), read(v);
        add_edge(u, v, i);
        add_edge(v, u, n + i - 1);
    }
    for (i = 1; i <= m; ++i) {
        read(u), read(v);
        query[u].push_back((Query) {v, i});
        query[v].push_back((Query) {u, i});
    }
    tarjan(root);
    for (i = 1; i <= m; ++i)
        printf("%d\n", ans[i]);
    return 0;
}
