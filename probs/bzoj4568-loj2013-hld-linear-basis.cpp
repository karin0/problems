#include <cstdio>
#include <cctype>
#include <algorithm>
#include <vector>
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
        return *s++; // return s == t ? EOF : *s++;
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
        return neg ? -x : x;
    }
    inline void pc(const char c) {
        if (p == b + L)
            fwrite(p = b, 1, L, stdout);
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
const int N = 20003, w = 60;
bool bit(const ll x, const int k) {
    return (x >> k) & 1ll;
}
struct Basis {
    ll b[w + 1]; // ***
    void insert(ll x) {
        int i, j;
        per (i, w, 0) {
            if (!x)
                return;
            if (!bit(x, i))
                continue;
            if (b[i])
                x ^= b[i];
            else {
                re (j, 0, i)
                    if (bit(x, j))
                        x ^= b[j];
                rep (j, i + 1, w)
                    if (bit(b[j], i))
                        b[j] ^= x;
                b[i] = x;
                return;
            }
        }
    }
    void merge_from(const Basis &c) {
        int i;
        rep (i, 0, w)
            if (c.b[i])
                insert(c.b[i]);
    }
    void clear() {
        int i;
        rep (i, 0, w)
            b[i] = 0;
    }
    ll query() const {
        int i;
		ll res = 0;
        rep (i, 0, w)
            res ^= b[i];
        return res;
    }
} req;
struct Node {
    int dep, dfn, siz;
    // BasisHandler *b;
    Node *top, *fa, *hch;
    ll x;
    struct Edge *e;
} g[N];
struct Edge {
    Node *v;
    Edge *e;
    Edge() {}
    Edge(Node *_u, Node *_v) : v(_v), e(_u->e) {
        _u->e = this;
    }
};
void arc(Node *u, Node *v) {
    static Edge pool[N * 2], *curr = pool;
    new (curr++) Edge(u, v);
    new (curr++) Edge(v, u);
}
int n;
struct SegT {
    SegT *lc, *rc;
    Basis b;
    SegT() {}
    SegT(ll x) {
        b.insert(x);
		//printf("I have %lld\n", b.query());
    }
    SegT(SegT *_lc, SegT *_rc) : lc(_lc), rc(_rc) {
        maintain();
    }
    void maintain() {
        b.merge_from(lc->b);
        b.merge_from(rc->b);
		//printf("I have %lld by them\n", b.query());
    }
    void query(int ql, int qr, int l = 1, int r = n) {
        if (ql <= l && r <= qr) {
			//printf("Gets in %d, %d For %d, %d itself has %lld\n", l, r, ql, qr, b.query());
			//printf("It is %lld\n", b.query());
            req.merge_from(b);
            return;
        }
        int mid = (l + r) >> 1;
        if (ql <= mid)
            lc->query(ql, qr, l, mid); // *********** lc!!
        if (qr > mid)
            rc->query(ql, qr, mid + 1, r);
    }
    void *operator new (size_t) {
        static SegT pool[N * 4], *curr = pool;
        return curr++;
    }
} *segt;
ll seq[N];
SegT *build(int l = 1, int r = n) {
    if (l == r)
        return /*printf("l = r = %d, x=%lld\n", l,seq[l]),*/ new SegT(seq[l]);
	//printf("l = %d, r  =%d !!\n",l,r);
    int mid = (l + r) >> 1;
    return new SegT(build(l, mid), build(mid + 1, r));
}
void dfs1(Node *u) {
    u->siz = 1;
    Node *v;
    for (Edge *e = u->e; e; e = e->e) if (!(v = e->v)->siz) {
        v->dep = u->dep + 1;
        v->fa = u;
        dfs1(v);
        u->siz += v->siz;
        if (!u->hch || v->siz > u->hch->siz)
            u->hch = v;
    }
}
void dfs2(Node *u, Node *t) {
    static int tim;
    u->dfn = ++tim;
	seq[tim] = u->x;  // ********
	//printf("%ld 's dfn = %d\n", u-g, u->dfn);
    u->top = t;
    /* if (!t->b)
        t->b = new BasisHandler;
    t->b->b.insert(u->x);*/
    if (u->hch)
        dfs2(u->hch, t);
    for (Edge *e = u->e; e; e = e->e) if (!e->v->dfn)
        dfs2(e->v, e->v);
}
ll query(Node *u, Node *v) {
    req.clear();
    while (u->top != v->top) {
        //printf("u = %ld, v = %ld\n", u-g, v-g);
        if (u->top->dep < v->top->dep)
            std::swap(u, v);
        segt->query(u->top->dfn, u->dfn);
        u = u->top->fa;
    }
    //printf("Fin u = %ld, v = %ld, udfn=%d, vdfn=%d\n", u-g, v-g, u->dfn, v->dfn);
    if (u->dep < v->dep)
        std::swap(u, v);
    segt->query(v->dfn, u->dfn); // ***
    return req.query();
}
void init() {
    static Node *rt = g + 1;
    dfs1(rt);
    dfs2(rt, rt);
    segt = build(1, n);
}
int main() {
    static int m, i;
    n = io;
    m = io;
    rep (i, 1, n)
        g[i].x = io;
    re (i, 1, n)
        arc(&g[(int)io], &g[(int)io]);
    init();
    rep (i, 1, m)
        io.print(query(&g[(int)io], &g[(int)io]));

    io.flush();
    return 0;
}
