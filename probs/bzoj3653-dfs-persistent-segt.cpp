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
        return s == t ? -1 : *s++;
    }
    void gs(char *st) {
        static char c;
        for (c = gc(); !isgraph(c); c = gc());
        *st++ = c;
        for (c = gc(); isgraph(c); c = gc())
            *st++ = c;
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
    void print(T x) {
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
    }
    void puts(const char *st) {
        while (*st)
            pc(*st++);
    }
    inline void flush() {
        fwrite(b, 1, p - b, stdout);
    }
} io;

const int N = 300003;
typedef long long ll;
void *alloc(size_t siz) {
    static const int S = N * 2 * sizeof(void *) * 2 + N * 20 * (sizeof(void *) * 2 + sizeof(ll));
    static char pool[S], *curr = pool, *p;
    if (curr + siz > pool + S)
        return malloc(siz);
    p = curr;
    curr += siz;
    return p;
}
int n, mdep;
struct SegT *null;
struct SegT {
    SegT *lc, *rc;
    ll v;
    SegT (SegT *_lc, SegT *_rc) : lc(_lc), rc(_rc), v(_lc->v + _rc->v) {}
    SegT (SegT *_lc, SegT *_rc, const ll _v) : lc(_lc), rc(_rc), v(_v) {}
    SegT *insert(const int l, const int r, const int i, const int x) const {
        if (l == r)
            return new (alloc(sizeof(SegT))) SegT(null, null, v + x);
        int mid = (l + r) >> 1;
        if (i <= mid)
            return new (alloc(sizeof(SegT))) SegT(lc->insert(l, mid, i, x), rc);
        else
            return new (alloc(sizeof(SegT))) SegT(lc, rc->insert(mid + 1, r, i, x));
    }
    SegT *insert(const int i, const int x) const {
        return insert(1, mdep, i, x);
    }
} *root[N];
ll query(const SegT *p, const SegT *q, const int l, const int r, const int ql, const int qr) {
    if (ql <= l && r <= qr)
        return p->v - q->v;
    int mid = (l + r) >> 1;
    ll res = 0;
    if (ql <= mid)
        res += query(p->lc, q->lc, l, mid, ql, qr);
    if (qr > mid)
        res += query(p->rc, q->rc, mid + 1, r, ql, qr);
    // printf("%d, %d, %d, %d Got %lld\n", l, r, ql, qr, res);
    return res;
}
struct Node {
    int dep, siz, dfn;
    struct Edge *e;
} g[N], *rdfn[N];
struct Edge {
    Node *v;
    Edge *e;
    Edge (Node *_u, Node *_v) : v(_v), e(_u->e) {
        _u->e = this;
    }
};
void dfs(Node *u) {
    static int tim;
    mdep = std::max(mdep, u->dep);
    u->dfn = ++tim;
    rdfn[tim] = u;
    u->siz = 1;
    Node *v;
    for (Edge *e = u->e; e; e = e->e)
        if (!(v = e->v)->dfn) {
            v->dep = u->dep + 1;
            dfs(v);
            u->siz += v->siz;
        }
}
void init() {
    static int i;
    g[1].dep = 1;
    dfs(&g[1]);
    null = new (alloc(sizeof(SegT))) SegT(NULL, NULL, 0);
    null->lc = null->rc = null;
    root[0] = null;
    for (i = 1; i <= n; ++i)
        root[i] = root[i - 1]->insert(rdfn[i]->dep, rdfn[i]->siz - 1);
}
inline ll query(Node *u, int k) {
    return (ll)(u->siz - 1) * std::min(u->dep - 1, k) + query(root[u->dfn + u->siz - 1], root[u->dfn], 1, mdep, u->dep, u->dep + k);
}
int main() {
    static int m, u, v, i;
    n = io, m = io;
    re (i, 1, n) {
        u = io, v = io;
        new (alloc(sizeof(Edge))) Edge(&g[u], &g[v]);
        new (alloc(sizeof(Edge))) Edge(&g[v], &g[u]);
    }
    init();
    while (m--) {
        u = io, v = io;
        io.print(query(&g[u], v));
        io.pc('\n');
    }

    io.flush();
    return 0;
}
