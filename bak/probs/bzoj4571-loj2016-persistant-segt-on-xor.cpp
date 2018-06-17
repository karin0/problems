#include <cstdio>
#include <cctype>
#include <cmath>
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

const int X = 100003, N = 200003, M = 100003, w = 17;
int mx;
struct SegT *nil;
struct SegT {
    SegT *lc, *rc;
    int cnt;
    SegT() {}
    SegT(SegT *_lc, SegT *_rc, int _c) : lc(_lc), rc(_rc), cnt(_c) {}
    SegT *insert(const int x, const int l = 0, const int r = mx) const {
        if (l == r)
            return new SegT(nil, nil, cnt + 1);
        int mid = (l + r) >> 1;
        if (x <= mid)
            return new SegT(lc->insert(x, l, mid), rc, cnt + 1);
        else
            return new SegT(lc, rc->insert(x, mid + 1, r), cnt + 1);
    }
    int query(int ql, int qr, int l = 0, int r = mx) const {
        if (!cnt)
            return 0;
        if (ql <= l && r <= qr)
            return cnt;
        int mid = (l + r) >> 1, res = 0;
        if (ql <= mid)
            res += lc->query(ql, qr, l, mid);
        if (qr > mid)
            res += rc->query(ql, qr, mid + 1, r);
        return res;
    }
    void *operator new (size_t) {
        static SegT pool[N * 20], *curr = pool;
        return curr++;
    }
} *segt[N];
bool query(int l, int r, int ql, int qr) {
    ql = std::max(ql, 0);
    qr = std::min(qr, mx);
    if (ql > qr)             // *****
        return false;
    return segt[r]->query(ql, qr) - segt[l - 1]->query(ql, qr);
}
int solve(int x, int b, int l, int r) {  // max (x xor (a_i + b))
    static int i, res, csn, t;
    res = csn = 0;
    per (i, w, 0) {
        t = 1 << i;
        if (x & t) { // x is 1 on i
            if (query(l, r, csn - b, (csn | t) - 1 - b))
                res |= t;
            else
                csn |= t;
        } else if (query(l, r, (csn | t) - b, csn + (t << 1) - 1 - b))
            res |= t, csn |= t;
    }
    return res;
}
int main() {
    nil = new SegT;
    nil->lc = nil->rc = nil;

    static int n, m, x, b, l, i, a[N];
    n = io;
    m = io;
    rep (i, 1, n)
        mx = std::max(mx, a[i] = io);
    segt[0] = nil;
    rep (i, 1, n)
        segt[i] = segt[i - 1]->insert(a[i]);
    while (m--) {
        x = io;
        b = io;
        l = io;
        io.print(solve(x, b, l, io));
    }

    io.flush();
    return 0;
}
