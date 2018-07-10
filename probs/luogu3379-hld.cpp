#include <cstdio>
#include <cstring>
#include <algorithm>
#define LC(x) ((x) << 1)
#define RC(x) (((x) << 1) | 1)
#define MID(x, y) ((x) + (((y) - (x)) >> 1))
#define MAXN 500010
int n, root, mod;

int adj[MAXN], n_val[MAXN];
int e_to[MAXN], e_next[MAXN], e_last = 0;
void add_edge(int u, int v) {
    ++e_last; // u -> v
    e_to[e_last] = v;
    e_next[e_last] = adj[u];
    adj[u] = e_last;

    ++e_last; // v -> u
    e_to[e_last] = u;
    e_next[e_last] = adj[v];
    adj[v] = e_last;
}

int fa[MAXN], hson[MAXN], depth[MAXN], size[MAXN];
int htop[MAXN], hld[MAXN], hld_last = 0; // tr_pos[MAXN];
void dfs1(int u, int deep) {
    int hson_size = -1;
    depth[u] = deep;
    size[u] = 1;
    
    int v;
    for (int e = adj[u]; e; e = e_next[e]) {
        v = e_to[e];
        if (v != fa[u]) {
            fa[v] = u;
            dfs1(v, deep + 1);
            size[u] += size[v]; // as subtree(v) is completely found
            if (size[v] > hson_size) {
                hson_size = size[v];
                hson[u] = v;
            }
        }
    }
} // u is leaf <=> hson[u] == 0 <=> size[u] == 1
void dfs2(int u, int top) {
    htop[u] = top;
    hld[u] = ++hld_last;
    tr_pos[hld_last] = u;
    if (!hson[u])
        return;
    dfs2(hson[u], top);
    int v, e;
    for (e = adj[u]; e; e = e_next[e]) {
        v = e_to[e];
        if (v != fa[u] && v != hson[u])
            dfs2(v, v);
    }
}
void update_path(int x, int y, int z) { // path(x, y)
    int tx = htop[x], ty = htop[y];
    while (tx != ty) {
        if (depth[tx] > depth[ty]) {
            std::swap(x, y);
            std::swap(tx, ty);
        }
        update(1, hld[ty], hld[y], z);
        y = fa[ty];
        ty = htop[y];
    }
    if (depth[x] > depth[y]) std::swap(x, y);
    update(1, hld[x], hld[y], z);
}
int query_path(int x, int y) {
    int res = 0;
    int tx = htop[x], ty = htop[y];
    while (tx != ty) {
        if (depth[tx] > depth[ty]) {
            std::swap(x, y);
            std::swap(tx, ty);
        }
        res += query(1, hld[ty], hld[y]);
        res %= mod;
        y = fa[ty];
        ty = htop[y];
    }
    if (depth[x] > depth[y]) std::swap(x, y); // To assume dep[x] < dep[y]
    res += query(1, hld[x], hld[y]);
    return res %= mod;
}

void hld_init() {
    dfs1(root, 0);
    dfs2(root, root);
}
int main() {
    int q;
    int x, y, z;
    scanf("%d%d%d%d", &n, &q, &root, &mod);
    for (int i = 1; i <= n; ++i ) {
        scanf("%d", n_val + i);
    }
    for (int i = 1; i < n; ++i) {
        scanf("%d%d", &x, &y);
        add_edge(x, y);
    }
    hld_init();
    int oper;
    while (q--) {
        scanf("%d", &oper);
        if (oper == 1) { // Add z to value of each node in path(x, y)
            scanf("%d%d%d", &x, &y, &z);
            update_path(x, y, z % mod);
        } else if (oper == 2) { // Query sum of values of nodes in path(x, y)
            scanf("%d%d", &x, &y);
            printf("%d\n", query_path(x, y));
        } else if (oper == 3) { // Add z to value of each node in sub-tree(x)
            scanf("%d%d", &x, &z);
            update(1, hld[x], hld[x] + size[x] - 1, z % mod); // as hld[] is continous in a sub-tree
        } else { // Query sum of values of nodes in sub-tree(x)
            scanf("%d", &x);
            printf("%d\n", query(1, hld[x], hld[x] + size[x] - 1) % mod); // as hld[] is continous in a sub-tree
        }
    }
}
