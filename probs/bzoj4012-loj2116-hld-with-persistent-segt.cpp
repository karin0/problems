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
        return neg ? -x : x;
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
    inline void flush() const {
        fwrite(b, 1, p - b, stdout); // p = b;
    }
} io;

typedef long long ll;
const int N = 150007, M = 200007;
int n;
struct Node {
    Node *fa, *hch, *top;
    int dfn, siz, dep, x, w;
    struct Edge *e;
} g[N], *ns[N], *rdfn[N], *rt;
struct Edge {
    Node *v;
    int w;
    Edge *e;
    Edge() {}
    Edge(Node *const _u, Node *const _v, const int _w) : v(_v), w(_w), e(_u->e) {
        _u->e = this;
    }
    void *operator new (size_t) {
        static Edge pool[N << 1], *curr = pool;
        return curr++;
    }
};
void dfs1(Node *const u) {
    u->siz = 1;
    Node *v;
    for (Edge *e = u->e; e; e = e->e) if (!(v = e->v)->siz) {
        v->fa = u;
        v->dep = u->dep + e->w; // *******************
        v->w = e->w;
        dfs1(v);
        u->siz += v->siz;
        if (!u->hch || u->hch->siz < v->siz)
            u->hch = v;
    }
}
void dfs2(Node *const u, Node *const t) {
    static int tim;
    u->dfn = ++tim;
    rdfn[tim] = u;
    u->top = t;
    if (u->hch)
        dfs2(u->hch, t);
    for (Edge *e = u->e; e; e = e->e)
        if (!e->v->dfn)
            dfs2(e->v, e->v);
}
int x[N], sw[N];
ll sd[N];
template <class T>
inline T csum(const T a[], const int l, const int r) {
    return a[r] - a[l - 1];
}
struct SegT {
    SegT *lc, *rc;
    ll sum, tag;
    SegT() {}
    SegT(SegT *const _lc, SegT *const _rc) : lc(_lc), rc(_rc), sum(_lc->sum + _rc->sum) {}
    SegT(SegT *const _lc, SegT *const _rc, const ll s, const int t) : lc(_lc), rc(_rc), sum(s), tag(t) {} // *********************** ll here!
    void *operator new (size_t) {
        static SegT pool[(N + M) * 43], *curr = pool;
        return curr++;
    }
    SegT *update(const int ql, const int qr, const int l = 1, const int r = n) const {
        if (ql <= l && r <= qr)
            return new SegT(lc, rc, sum + csum(sw, l, r), tag + 1);
        int mid = (l + r) >> 1;
        SegT *p = new SegT(lc, rc, 0, tag);
        if (ql <= mid)
            p->lc = lc->update(ql, qr, l, mid);
        if (qr > mid)
            p->rc = rc->update(ql, qr, mid + 1, r);
        p->sum = p->lc->sum + p->rc->sum + tag * csum(sw, l, r); // ************ calc this later
        return p;
    }
    ll query(const int ql, const int qr, const int l = 1, const int r = n, ll t = 0) const {
        if (ql <= l && r <= qr)
            return sum + t * csum(sw, l, r);
        int mid = (l + r) >> 1;
        ll res = 0;
        t += tag;
        if (ql <= mid)
            res += lc->query(ql, qr, l, mid, t);
        if (qr > mid)
            res += rc->query(ql, qr, mid + 1, r, t);
        return res;
    }
} *segt[N], *nil;
SegT *update(SegT *o, const Node *u) {
    while (u) {
    // while (u->top != rt) {
        o = o->update(u->top->dfn, u->dfn);
        u = u->top->fa;
    }
    // if (u != rt)
    //    o = o->update(rt->dfn + 1, u->dfn);
    return o;
}
ll query(const int l, const int r, const Node *u) {
    static ll res;
    static int ql, qr;
    static SegT *p, *q;
    res = 0;
    p = segt[l - 1];
    q = segt[r]; 
    //while (u->top != rt) {
    while (u) {
        ql = u->top->dfn;
        qr = u->dfn;
        res += q->query(ql, qr);
        if (p != nil)
            res -= p->query(ql, qr);
        u = u->top->fa;
    }
    /* if (u != rt) {
        ql = rt->dfn + 1;
        qr = u->dfn;
        res += q->query(ql, qr);
        if (p != nil)
            res -= p->query(ql, qr);
    } */
    return res;
}
inline bool ncmp(const Node *u, const Node *v) {
    return u->x < v->x;
}
void init() {
    static int i;
    nil = new SegT;
    nil->lc = nil->rc = nil;
    rt = &g[2];
    // rt->dep = 0;
    dfs1(rt);
    dfs2(rt, rt);
    rep (i, 1, n)
        sw[i] = sw[i - 1] + rdfn[i]->w;
    std::sort(ns + 1, ns + n + 1, ncmp);
    segt[0] = nil;
    rep (i, 1, n) {
        sd[i] = sd[i - 1] + ns[i]->dep;
        x[i] = ns[i]->x;
        segt[i] = update(segt[i - 1], ns[i]);
    }
}

inline ll calc(const Node *const u, int l, int r) {
    l = std::lower_bound(x + 1, x + n + 1, l) - x;
    r = std::upper_bound(x + 1, x + n + 1, r) - x - 1;
    return (ll)u->dep * (r - l + 1) + csum(sd, l, r) - 2ll * query(l, r, u);
}
int main() {
    static int m, i, mx;
    n = io;
    m = io;
    mx = io;
    rep (i, 1, n) {
        g[i].x = io;
        ns[i] = &g[i];
    }
    re (i, 1, n) {
        static int u, v, w;
        u = io;
        v = io;
        w = io;
        new Edge(&g[u], &g[v], w);
        new Edge(&g[v], &g[u], w);
    }
    init();
    while (m--) {
        static ll la;
        static int u, l, r;
        u = io;
        l = ((ll)io + la) % mx;
        r = ((ll)io + la) % mx;
        if (l > r)
            std::swap(l, r);
        io.print(la = calc(&g[u], l, r));
    }

    io.flush(); // ***
    return 0;
}
