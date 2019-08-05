#include <cstdio>
#include <algorithm>
#include <new>

const int N = 100005, B = 12 * N * 8, E = 600005;

size_t nsiz;
void *alloc() {
    static char buf[B], *cur = buf, *p;
    if (cur + nsiz > buf + B)
        return malloc(nsiz);
    p = cur;
    cur += nsiz;
    return p;
}
int n, mx, en;
struct SegT *null;
struct SegT {
    SegT *lc, *rc;
    int cnt;
    SegT (SegT *_lc, SegT *_rc) : lc(_lc), rc(_rc), cnt(_lc->cnt + _rc->cnt) {}
    SegT (SegT *_lc, SegT *_rc, const int _c) : lc(_lc), rc(_rc), cnt(_c) {}
    
    SegT *insert(const int l, const int r, const int x) {
        if (l == r)
            return new (alloc()) SegT(null, null, cnt + 1);
        int mid = (l + r) >> 1;
        if (x <= mid)
            return new (alloc()) SegT(lc->insert(l, mid, x), rc);
        else
            return new (alloc()) SegT(lc, rc->insert(mid + 1, r, x));
    }
    SegT *insert(const int x) {
        return insert(1, mx, x);
    }
    inline int rank() const {
        return lc->cnt;
    }
};
void ct_init() {
    nsiz = sizeof(SegT);
    null = new (alloc()) SegT(NULL, NULL, 0);
    null->lc = null->rc = null;
}
struct Node {
    SegT *seg;
    int x, efn, dep;
    Node *fa;
    struct Edge *e;
} g[N], *st[E][20];
struct Edge {
    Node *v;
    Edge *e;
    Edge(Node *_u, Node *_v) : v(_v), e(_u->e) {
        _u->e = this;
    }
};
void dfs(Node *u) {
    st[++en][0] = u;
    u->efn = en;
    if (u->fa)
        u->seg = u->fa->seg->insert(u->x);
    for (Edge *e = u->e; e; e = e->e) if (!e->v->efn) {
        e->v->dep = u->dep + 1;
        e->v->fa = u;
        dfs(e->v);
        st[++en][0] = u;
    }
}
int lg[E];
void st_init() {
    static int i, j;
    for (i = 2; i <= en; ++i)
        lg[i] = lg[i - 1] + ((1 << (lg[i - 1] + 1)) <= i); // printf("lg[%d]=%d\n",i,lg[i]);
    for (j = 1; (1 << j) <= en; ++j)
        for (i = 1; i + (1 << j) - 1 <= en; ++i) {
            if (st[i][j - 1]->dep < st[i + (1 << (j - 1))][j - 1]->dep)
                st[i][j] = st[i][j - 1];
            else
                st[i][j] = st[i + (1 << (j - 1))][j - 1];
        }
}
Node *lca(const Node *u, const Node *v) {
    static int l, r, k;
    l = u->efn, r = v->efn;
    if (l > r)
        std::swap(l, r);
    k = lg[r - l + 1];
    if (st[l][k]->dep < st[r - (1 << k) + 1][k]->dep)
        return st[l][k];
    else
        return st[r - (1 << k) + 1][k];
}
int query(const Node *u, const Node *v, int k) {
    static SegT *ut, *vt, *pt, *ft;
    static int lb, rb, t, mid;
    static Node *p;
    p = lca(u, v);
    ut = u->seg, vt = v->seg, pt = p->seg, ft = p->fa ? p->fa->seg : null;
    lb = 1, rb = mx;
    while (lb < rb) {
        t = ut->rank() + vt->rank() - pt->rank() - ft->rank();
        mid = (lb + rb) >> 1;
        if (k <= t)
            ut = ut->lc, vt = vt->lc, pt = pt->lc, ft = ft->lc, rb = mid;
        else
            ut = ut->rc, vt = vt->rc, pt = pt->rc, ft = ft->rc, lb = mid + 1, k -= t;
    }
    return lb;
}
int main() {
    static int m, set[N], i, *end, u, v, k, la;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i)
        scanf("%d", &set[i]), g[i].x = set[i];
    std::sort(set + 1, set + n + 1);
    end = std::unique(set + 1, set + n + 1);
    mx = end - set - 1;
    for (i = 1; i <= n; ++i)
        g[i].x = std::lower_bound(set + 1, end, g[i].x) - set;
    for (i = 1; i < n; ++i) {
        scanf("%d%d", &u, &v);
        new Edge(&g[u], &g[v]);
        new Edge(&g[v], &g[u]);
    }
    ct_init();
    g[1].dep = 1;
    g[1].seg = null->insert(g[1].x);
    dfs(&g[1]);
    st_init();
    while (m--) {
        scanf("%d%d%d", &u, &v, &k);
        printf("%d", la = set[query(&g[u ^ la], &g[v], k)]);
        if (m)
            putchar('\n');
    }
    

    return 0;
}
