#include <cstdio>
#include <cctype>
#include <algorithm>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))

struct IO {
    static const int L = 1000000;
    char a[L], b[L], *s, *t, *p;
    IO() : p(b) {}
    inline char gc() {
        if (s == t)
            t = (s = a) + fread(a, 1, L, stdin);
        return *s++; // return s == t ? -1 : *s++;
    }
    void gs(char *st) {
        static char c;
        for (c = gc(); !isgraph(c); c = gc());
        *st++ = c;
        for (c = gc(); isgraph(c); c = gc())
            *st++ = c;
        *st++ = 0;
    }
    template <class T>
    operator T() {
        static T x;
        static char c;
        static bool neg;
        for (c = gc(); c != '-' && !isdigit(c); c = gc());
        if (c == '-')
            neg = true, c = gc();
        else
            neg = false;
        x = c - '0';
        for (c = gc(); isdigit(c); c = gc())
            x = x * 10 + (c - '0');
        if (neg)
            x = -x;
        return x;
    }
    inline void pc(const char c) {
        if (p == b + L)
            fwrite(b, 1, L, stdout), p = b;
        *p++ = c;
    }
    template<class T>
    void print(T x, const bool nl = true) {
        static char c[30], *q;
        static T y;
        if (x == 0)
            pc('0');
        else {
            if (x < 0)
                pc('-'), x = -x;
            for (q = c; x; x = y)
                y = x / 10, *q++ = x - y * 10 + '0';
            while (q != c)
                pc(*--q);
        }
        if (nl)
            pc('\n');
    }
    void ps(const char *st, const bool nl = true) {
        while (*st)
            pc(*st++);
        if (nl)
            pc('\n');
    }
    inline void flush() const {
        fwrite(b, 1, p - b, stdout); // p = b;
    }
} io;

typedef long long ll;
const int N = 100007;
int n;
struct SegT *nil;
struct SegT {
    SegT *lc, *rc;
    int cnt;

    SegT() {}
    SegT(SegT * const _lc, SegT * const _rc) : lc(_lc), rc(_rc), cnt(_lc->cnt + rc->cnt) {}
    SegT(const int _c) : lc(nil), rc(nil), cnt(_c) {}
    void *operator new (size_t) {
        static SegT pool[N * 18], *curr = pool;
        return curr++;
    }
    SegT *insert(const int x, const int l = 1, const int r = n) const {
        // printf("Ins %d in %d, %d\n", x, l, r);
        if (l == r)
            return new SegT(cnt + 1);
        int mid = (l + r) >> 1;
        if (x <= mid)
            return new SegT(lc->insert(x, l, mid), rc);
        else
            return new SegT(lc, rc->insert(x, mid + 1, r));
    }
    inline int rank() const {
        return lc->cnt;
   }
} *segt[N];
int query_kth(const int ql, const int qr, int k) {
    static SegT *p, *q;
    static int l, r, mid, t;
    // printf("Ans for %d, %d, %d is ", ql, qr, k);
    p = segt[ql - 1], q = segt[qr];
    l = 1, r = n; // ***
    while (l < r) {
        t = q->rank() - p->rank();
        mid = (l + r) >> 1;
        if (k <= t)
            p = p->lc, q = q->lc, r = mid;
        else
            p = p->rc, q = q->rc, l = mid + 1, k -= t;
    }
    // printf("%d\n", l);
    return l;
}
int seq[N];
struct Node {
    int dep, dfn, siz;
    Node *hch, *top, *fa;
    struct Edge *e;
} g[N];
struct Edge {
    Node *v;
    Edge *e;

    Edge() {}
    Edge(Node * const _u, Node * const _v) : v(_v), e(_u->e) {
        _u->e = this;
    }
    void *operator new (size_t) {
        static Edge pool[N * 2], *curr = pool;
        return curr++;
    }
};
void dfs1(Node *u) {
    u->siz = 1;
    Node *v;
    // printf("Dep of %d is %d\n", u-g, u->dep);
    for (Edge *e = u->e; e; e = e->e) if (!(v = e->v)->siz) {
        v->fa = u;
        v->dep = u->dep + 1;
        dfs1(v);
        u->siz += v->siz;
        if (!u->hch || v->siz > u->hch->siz)
            u->hch = v;
    }
}
void dfs2(Node *u, Node *t) {
    static int tim;
    u->top = t;
    u->dfn = ++tim;
    seq[tim] = u - g;
    if (u->hch)
        dfs2(u->hch, t);
    for (Edge *e = u->e; e; e = e->e)
        if (!e->v->dfn && e->v != u->hch)
            dfs2(e->v, e->v);
}
Node *query_kth_node(Node *u, int k) {
    return &g[query_kth(u->dfn, u->dfn + u->siz - 1, k)];
}
struct VNode {
    Node *src, *ofa;
    ll dep;
    int siz, dfn;
    VNode *fa, *hch, *top;
    struct VEdge *e;

    VNode() {}
    VNode(Node *_s, Node *_o) : src(_s), ofa(_o) {}
    void *operator new (size_t) {
        static VNode pool[N], *curr = pool;
        return curr++;
    }
} *vt, *vrdfn[N];
struct VEdge {
    int w;
    VNode *v;
    VEdge *e;

    VEdge() {}
    VEdge(VNode * const _u, VNode * const _v, const int _w) : w(_w), v(_v), e(_u->e) {
        // printf("%d to %d, w = %d\n", _u->src-g, _v->src-g, w);
        _u->e = this;
    }
    void *operator new (size_t) {
        static VEdge pool[N], *curr = pool;
        return curr++;
    }
};
void vdfs1(VNode *u) {
    u->siz = 1;
    VNode *v;
    for (VEdge *e = u->e; e; e = e->e) {
        v = e->v;
        // printf("S%ld to S%ld\n", u->src-g, v->src-g);
        v->fa = u;
        v->dep = u->dep + e->w;
        vdfs1(v);
        u->siz += v->siz;
        if (!u->hch || v->siz > u->hch->siz)
            u->hch = v;
    }
    // printf("S%ld dep=%d, siz=%d\n", u->src-g, u->dep, u->siz);
}
void vdfs2(VNode *u, VNode *t) {
    static int tim;
    u->dfn = ++tim;
    vrdfn[tim] = u;
    u->top = t;
    if (u->hch)
        vdfs2(u->hch, t);
    for (VEdge *e = u->e; e; e = e->e)
        if (e->v != u->hch)
            vdfs2(e->v, e->v);
}
template <typename T>
T *lca(T *u, T *v) {
    while (u->top != v->top) {
        if (u->top->dep < v->top->dep)
            std::swap(u, v);
        u = u->top->fa;
    }
    if (u->dep < v->dep)
        std::swap(u, v);
    return v;
}
VNode *to_down(VNode *u, const VNode *const f) {
    static VNode *t;
    while (u->top != f->top) {
        t = u->top->fa;
        if (t == f)
            return u->top;
        u = t;
    }
    return vrdfn[f->dfn + 1];
}
inline void init1() {
    static int i;
    nil = new SegT(0);
    nil->lc = nil->rc = nil;
    g[1].dep = 1;
    dfs1(&g[1]);
    dfs2(&g[1], &g[1]);
    segt[0] = nil;
    rep (i, 1, n)
        segt[i] = segt[i - 1]->insert(seq[i]);
}
inline void init2() {
    vt->dep = 1;
    vdfs1(vt);
    vdfs2(vt, vt);
}
struct Rec {
    ll cnt;
    VNode *u;
    bool operator < (const Rec &rhs) {
        return cnt < rhs.cnt;
    }
} qaq[N];
int m;
inline Rec *find(const ll u) {
    return std::lower_bound(qaq, qaq + m + 1, (Rec){u, NULL});
}
inline Node *find_origin(const ll u, const Rec * const r) {
    return query_kth_node(r->u->src, (r == qaq) ? u : (u - (r - 1)->cnt));
}
int main() {
    static int qq, i;
    n = io, m = io, qq = io;
    re (i, 1, n) {
        static int u, v;
        u = io, v = io;
        new Edge(&g[u], &g[v]);
        new Edge(&g[v], &g[u]);
    }
    init1();
    qaq[0].cnt = n;
    qaq[0].u = vt = new VNode(&g[1], NULL);
    rep (i, 1, m) {
        static int u;
        static ll f;
        static Rec *r;
        static Node *o;
        u = io, f = io;
        r = std::lower_bound(qaq, qaq + i, (Rec){f, NULL});
        // printf("%ld %lld %d\n", r - qaq, r->cnt, (int)(r->u->src == &g[1]));
        o = find_origin(f, r);
        qaq[i].u = new VNode(&g[u], o);
        qaq[i].cnt = qaq[i - 1].cnt + g[u].siz;
        new VEdge(r->u, qaq[i].u, o->dep - r->u->src->dep + 1);
    }
    init2();
    rep (i, 1, qq) {
        static ll u, v;
        static Rec *bu, *bv;
        static Node *ou, *ov;
        static VNode *vu, *vv, *q, *t;
        u = io, v = io;
        bu = find(u), bv = find(v);
        ou = find_origin(u, bu);
        ov = find_origin(v, bv);
        if (bu == bv) {
            Node *p = lca(ou, ov);
            io.print(ou->dep + ov->dep - p->dep * 2);
        } else {
            vu = bu->u, vv = bv->u;
            VNode *p = lca(vu, vv);
            if (p == vu) {
                q = to_down(vv, vu);
                io.print(vv->dep - q->dep + 1 + q->ofa->dep + ou->dep - lca(q->ofa, ou)->dep * 2 + ov->dep - vv->src->dep);
            } else if (p == vv) {
                q = to_down(vu, vv);
                io.print(vu->dep - q->dep + 1 + q->ofa->dep + ov->dep - lca(q->ofa, ov)->dep * 2 + ou->dep - vu->src->dep);
            } else {
                q = to_down(vu, p);
                t = to_down(vv, p);
                io.print(vu->dep - q->dep + vv->dep - t->dep + 2 + q->ofa->dep + t->ofa->dep - lca(q->ofa, t->ofa)->dep * 2 + ou->dep - vu->src->dep + ov->dep - vv->src->dep);
            }
        }
    }

    io.flush(); // ***
    return 0;
}
