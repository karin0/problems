#include <cstdio>
#include <algorithm>
#define LC(x) ((x) << 1)
#define RC(x) (((x) << 1) | 1)
#define MID(x, y) ((x) + (((y) - (x)) >> 1))
#define MAXN 500010

// Graph
int n;
int adj[MAXN], e_to[MAXN], e_next[MAXN], e_last;

void add_edge(int u, int v) {
    ++e_last;
    e_to[e_last] = v;
    e_next[e_last] = adj[u];
    adj[u] = e_last;
    
    ++e_last;
    e_to[e_last] = u;
    e_next[e_last] = adj[v];
    adj[v] = e_last;
}
// Segment Tree
struct Segment {
    int val, tag, l, r;
    // Maintain num of 1 nodes
    // tag is the status that all nodes in its subtree should be
};
Segment st[4 * MAXN];
void build(int k, int l, int r) {
    st[k].l = l;
    st[k].r = r;
    st[k].tag = -1;
    st[k].val = 0;
    if (l != r) {
        int mid = MID(l, r);
        build(LC(k), l, mid);
        build(RC(k), mid + 1, r);
    }
}
void unlazy(int k) {
    int t = st[k].tag;
    st[LC(k)].tag = t;
    st[RC(k)].tag = t;
    st[k].tag = -1;
    if (t) {
        st[LC(k)].val = st[LC(k)].r - st[LC(k)].l + 1;
        st[RC(k)].val = st[RC(k)].r - st[RC(k)].l + 1;
    } else {
        st[LC(k)].val = 0;
        st[RC(k)].val = 0;
    }
}
int act(int k, int tl, int tr, int v) { // Update all to v, query nums of 0^d
    Segment &seg = st[k];
    if (tr < seg.l || seg.r < tl) return 0;
    if (tl <= seg.l && seg.r <= tr) { // Insider & Outsider
        int ans;
        seg.tag = v;
        if (v) {
            ans = seg.r - seg.l + 1 - seg.val;
            seg.val = seg.r - seg.l + 1;
        } else {
            ans = seg.val;
            seg.val = 0;
        }
        return ans;
    } else {
        if (seg.tag != -1) unlazy(k);
        int ans = act(LC(k), tl, tr, v) + act(RC(k), tl, tr, v);
        seg.val = st[LC(k)].val + st[RC(k)].val; // Remember to push up!
        return ans;
    }
}
// Tree with HLD
int fa[MAXN], siz[MAXN], dep[MAXN];
int hld[MAXN], htop[MAXN], hson[MAXN], hld_last;
void dfs1(int u, int deep) {
    siz[u] = 1;
    dep[u] = deep;
    int hson_size = -1;
    
    int v;
    for (int e = adj[u]; e; e = e_next[e]) {
        v = e_to[e];
        if (v != fa[u]) {
            fa[v] = u;
            dfs1(v, deep + 1);
            siz[u] += siz[v];
            if (siz[v] > hson_size) {
                hson_size = siz[v];
                hson[u] = v;
            }
        }
    }
}
void dfs2(int u, int top) {
    htop[u] = top;
    hld[u] = ++hld_last;
    // tr[hld_last] = u;
    if (!hson[u]) return;
    dfs2(hson[u], top);
    
    int v;
    for (int e = adj[u]; e; e = e_next[e]) {
        v = e_to[e];
        if (v != fa[u] && v != hson[u]) {
            dfs2(v, v);
        }
    }
}
void hld_init() {
    dfs1(0, 0);
    dfs2(0, 0);
    build(1, 1, n);
}
int act_to_root(int x, int v) {
    int res = 0;
    while (htop[x] != 0) {
        res += act(1, hld[htop[x]], hld[x], v);
        x = fa[htop[x]];
    }
    res += act(1, hld[0], hld[x], v);
    return res;
}

//
int main() {
    int q, v;
    scanf("%d", &n);
    for (int u = 1; u < n; ++u) {
        scanf("%d", &v);
        add_edge(u, v);
    }
    hld_init(); // Remember this!
    scanf("%d", &q);
    while (q--) {
        char oper[10];
        int x;
        scanf("%s%d", oper, &x);
        if (oper[0] == 'i') {    
            // Update the 0 nodes on path(0, x) to 1 and query the num
            printf("%d\n", act_to_root(x, 1));
        } else {
            // Update the 1 nodes in subtree(x) to 0 and query the num
            printf("%d\n", act(1, hld[x], hld[x] + siz[x] - 1, 0));
        }
    }
    return 0;
}
