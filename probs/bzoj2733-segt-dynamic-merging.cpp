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
const int N = 100004;
struct UnionFind {
    int fa[N];
    void init(const int n) {
        static int i;
        rep (i, 1, n)
            fa[i] = i;
    }
    int find(const int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
    inline void link(const int x, const int y) {
        fa[x] = y;
    }
} uf;
int n, val[N], rval[N];
struct SegT {
    int cnt;
    SegT *lc, *rc;

    int query(const int k, const int l = 1, const int r = n) {
        int rk = lc ? lc->cnt : 0;
        if (l == r)
            return l;
        int mid = (l + r) >> 1;
        if (k < rk)
            return lc->query(k, l, mid);
        else
            return rc->query(k - rk, mid + 1, r);
    }
} pool[(N + N) * 18], *curr = pool, *segt[N];
void insert(SegT *&o, const int i, const int l = 1, const int r = n) {
    if (!o)
        o = new (curr++) SegT;
    if (l == i && r == i) {
        ++o->cnt;
        return;
    }
    int mid = (l + r) >> 1;
    if (i <= mid)
        insert(o->lc, i, l, mid);
    else
        insert(o->rc, i, mid + 1, r);
    ++o->cnt; // o->maintain();
}
SegT *merge(SegT *p, SegT *q) {
    if (!p)
        return q;
    if (!q)
        return p;
    if (p->cnt > q->cnt)
        std::swap(p, q);
    q->cnt += p->cnt; // in spite of q->maintain();
    q->lc = merge(p->lc, q->lc);
    q->rc = merge(p->rc, q->rc);
    return q;
}

int main() {
    static int m, q, i, u, v;
    static char op[4];
    n = io, m = io;
    uf.init(n);
    rep (i, 1, n)
        rval[val[i] = io] = i;
    rep (i, 1, m)
        uf.link(uf.find(io), uf.find(io));
    rep (i, 1, n)
        insert(segt[uf.find(i)], val[i]);
    q = io;
    while (q--) {
        io.gs(op);
        u = uf.find(io);
        v = io;
        if (op[0] == 'B') {
            v = uf.find(v);
            if (u == v)
                continue;
            if (segt[u]->cnt > segt[v]->cnt)
                std::swap(u, v);
            uf.link(u, v);
            segt[v] = merge(segt[u], segt[v]);
        } else {
            --v;
            if (segt[u]->cnt <= v)
                io.ps("-1");
            else
                io.print(rval[segt[u]->query(v)]);
        }
    }

    io.flush(); // ***
    return 0;
}
