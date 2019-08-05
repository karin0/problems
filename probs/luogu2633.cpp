#include <akari>

IO<1000000, 1000000> io;

cint N = 100002;

struct SegT *curr, *nil;
struct SegT {
    SegT *lc, *rc;
    int w;
    SegT() {}
    SegT(SegT *l, SegT *r, cint w) : lc(l), rc(r), w(w) {}
    SegT *insert(cint l, cint r, cint x) const {
        if (l == r)
            return new (curr++) SegT(lc, rc, w + 1);
        int mid = (l + r) >> 1;
        if (x <= mid)
            return new (curr++) SegT(lc->insert(l, mid, x), rc, w + 1);
        else
            return new (curr++) SegT(lc, rc->insert(mid + 1, r, x), w + 1);
    }
} pool[N * 32];
int mx;

struct Edge;
struct Node {
    SegT *segt;
    int dep, siz, dfn;
    ll w;
    Node *hch, *fa, *top;
    Edge *e;
} g[N];
struct Edge {
    Node *u, *v;
    Edge *e;
    Edge() {}
    Edge(Node *u, Node *v, Edge *e) : u(u), v(v), e(e) {}
} pool_e[N << 1], *curr_e = pool_e;
void arc(Node *u, Node *v) {
    u->e = new (curr_e++) Edge(u, v, u->e);
    v->e = new (curr_e++) Edge(v, u, v->e);
}
void dfs1(Node *u, Node *f) {
    u->segt = (f ? f->segt : nil)->insert(1, mx, u->w);
    u->siz = 1;
    Node *v;
    go (e, u->e) if ((v = e->v) != f) {
        v->fa = u;
        v->dep = u->dep + 1;
        dfs1(v, u);
        u->siz += v->siz;
        if (!u->hch || v->siz > u->hch->siz)
            u->hch = v;
    }
}
void dfs2(Node *u, Node *t) {
    u->top = t;
    Node *v;
    go (e, u->e) if ((v = e->v) != u->fa)
        dfs2(v, (v == u->hch) ? t : v);
}
Node *lca(Node *u, Node *v) {
    while (u->top != v->top) {
        if (u->top->dep < v->top->dep)
            std::swap(u, v);
        u = u->top->fa;
    }
    return (u->dep < v->dep) ? u : v;
}

int query(Node *u, Node *v, int k) {
    Node *o = lca(u, v);
    SegT *a = u->segt, *b = v->segt, *c = o->segt, *d = o->fa ? o->fa->segt : nil;
    int l = 1, r = mx;
    while (l < r) {
        int x = a->lc->w + b->lc->w - c->lc->w - d->lc->w;
        int mid = (l + r) >> 1;
        if (k <= x)
            a = a->lc, b = b->lc, c = c->lc, d = d->lc, r = mid;
        else
            a = a->rc, b = b->rc, c = c->rc, d = d->rc, l = mid + 1, k -= x; // ***
    }
    return l;
}

ll a[N];
int main() {
    curr = pool;
    nil = new (curr++) SegT;
    nil->lc = nil->rc = nil;

    int n, m;
    io >> n >> m;
    rep (i, 1, n)
        a[i] = g[i].w = io;
    std::sort(a + 1, a + n + 1);
    ll *end = std::unique(a + 1, a + n + 1);
    mx = end - a - 1;
    rep (i, 1, n)
        g[i].w = std::lower_bound(a + 1, end, g[i].w) - a;

    re (i, 1, n) {
        int u, v;
        io >> u >> v;
        arc(&g[u], &g[v]);
    }
    Node *rt = &g[1];
    dfs1(rt, NULL);
    dfs2(rt, rt);

    ll la = 0;
    rep (i, 1, m) {
        int u = (ll)io ^ la, v, k;
        io >> v >> k;
        ccc(u, v, k);
        io << (la = a[query(&g[u], &g[v], k)]) daze;
    }


    return 0;
}
