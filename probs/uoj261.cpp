#include <cstdio>
#include <vector>

const int MAXV = 3e5 + 5, MAXE = 6e5 + 10, MAXM = 3e5 + 5;

int n, adj[MAXV], w[MAXV], to[MAXE], next[MAXE];
inline void add_edge(int u, int v, int e) {
    to[e] = v;
    next[e] = adj[u];
    adj[u] = e;
}

int pa[MAXV];
inline int find(int x) {
    return pa[x] == x ? x : pa[x] = find(pa[x]);
}

int fa[MAXV], depth[MAXV], begin[MAXV], stamp = 0, ans1[MAXV], ans2[MAXV];
std::vector<int> as_begin_of_node[MAXV], as_end_of_node[MAXV], as_begin_of_path[MAXV], as_end_of_path[MAXV], as_begin_of_path2[MAXV], as_end_of_path2[MAXV];
struct Query {
    int v, id;
};
int s[MAXM], t[MAXM], lca[MAXM];
std::vector<Query> query[MAXV];
inline void tarjan(int u, int deep) {
    as_begin_of_node[++stamp].push_back(u);
    begin[u] = stamp;
    depth[u] = deep;
    pa[u] = u;
    for (Query *q = &query[u].front(); q && q <= &query[u].back(); ++q)
        if (fa[q -> v] && !lca[q -> id])
            lca[q -> id] = find(q -> v);
    for (int e = adj[u], v; e; e = next[e]) {
        v = to[e];
        if (!fa[v]) {
            fa[v] = u;
            tarjan(v, deep + 1);
            pa[v] = u;
        }
    }
    as_end_of_node[stamp].push_back(u);
    // end[u] = stamp;
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

int cnt1[MAXV * 4], cnt2[MAXV * 4];
int main() {
    int i, m, u, v;
    read(n), read(m);
    for (i = 1; i < n; ++i) {
        read(u), read(v);
        add_edge(u, v, i);
        add_edge(v, u, n + i - 1);
    }
    for (i = 1; i <= n; ++i)
        read(w[i]);
    for (i = 1; i <= m; ++i) {
        read(s[i]), read(t[i]);
        query[s[i]].push_back(Query{t[i], i});
        query[t[i]].push_back(Query{s[i], i});
    }
    fa[1] = -1;
    tarjan(1, 0);
    for (i = 1; i <= m; ++i) {
        as_begin_of_path[begin[s[i]]].push_back(i);
        as_end_of_path[begin[lca[i]]].push_back(i);
    }
    int *pu;
    for (i = 1; i <= n; ++i) {
        for (pu = &as_begin_of_node[i].front(); pu && pu <= &as_begin_of_node[i].back(); ++pu) {
            u = *pu;
            ans1[u] = cnt1[depth[u] - w[u] + n];
            // w[j] = depth[j] - depth[s_i]
        }
        for (pu = &as_begin_of_path[i].front(); pu && pu <= &as_begin_of_path[i].back(); ++pu) {
            u = *pu;
            ++cnt1[depth[s[u]] + n];
        }
        for (pu = &as_end_of_path[i].front(); pu && pu <= &as_end_of_path[i].back(); ++pu) {
            u = *pu;
            --cnt1[depth[s[u]] + n];
        }
        for (pu = &as_end_of_node[i].front(); pu && pu <= &as_end_of_node[i].back(); ++pu) {
            u = *pu;
            ans1[u] = cnt1[depth[u] - w[u] + n] - ans1[u];
        }
    }
    for (i = 1; i <= m; ++i) {
        as_begin_of_path2[begin[t[i]]].push_back(i);
        as_end_of_path2[begin[fa[lca[i]]]].push_back(i);
    }
    for (i = 1; i <= n; ++i) {
        for (pu = &as_begin_of_node[i].front(); pu && pu <= &as_begin_of_node[i].back(); ++pu) {
            u = *pu;
            ans2[u] = cnt2[depth[u] - w[u] + n];
            // w[j] = depth[j] - depth[lca_i] + (depth[s_i] - depth[lca_i])
            // depth[j] - w[j] = 2 * depth[lca_i] - depth[s_i]
        }
        for (pu = &as_begin_of_path2[i].front(); pu && pu <= &as_begin_of_path2[i].back(); ++pu) {
            u = *pu;
            ++cnt2[depth[lca[u]] * 2 - depth[s[u]] + n];
        }
        for (pu = &as_end_of_path2[i].front(); pu && pu <= &as_end_of_path2[i].back(); ++pu) {
            u = *pu;
            --cnt2[depth[lca[u]] * 2 - depth[s[u]] + n];
        }
        for (pu = &as_end_of_node[i].front(); pu && pu <= &as_end_of_node[i].back(); ++pu) {
            u = *pu;
            ans2[u] = cnt2[depth[u] - w[u] + n] - ans2[u];
        }
    }
    for (i = 1; i <= n; ++i)
        printf("%d ", ans1[i] + ans2[i]);
    printf("\n");
    return 0;
}
