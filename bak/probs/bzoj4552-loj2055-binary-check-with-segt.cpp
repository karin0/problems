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
const int N = 100003;
int n;
struct Query {
    bool op;
    int l, r;
} qwq[N];
struct SegT {
    int len, sum, tag;
    SegT *lc, *rc;

    SegT () {}
    SegT (const int _v) : len(1), sum(_v), tag(-1) {}
    SegT (const int _l, SegT * const _lc, SegT * const _rc) : len(_l), tag(-1), lc(_lc), rc(_rc) {
        maintain();
    }
    inline void maintain() {
        sum = lc->sum + rc->sum;
    }
    inline void cover(const bool x) {
        sum = x ? len : 0;
        tag = x; // ***
    }
    inline void push_down() {
        if (tag >= 0) {
            lc->cover(tag);
            rc->cover(tag);
            tag = -1;
        }
    }
    inline int query(const int ql, const int qr, const int l = 1, const int r = n) {
        if (ql <= l && r <= qr)
            return sum;
        push_down();
        int mid = (l + r) >> 1, res = 0;
        if (ql <= mid)
            res += lc->query(ql, qr, l, mid);
        if (qr > mid)
            res += rc->query(ql, qr, mid + 1, r);
        return res;
    }
    inline void update(const int ql, const int qr, const bool x, const int l = 1, const int r = n) {
        if (ql <= l && r <= qr) {
            cover(x);
            return;
        }
        push_down();
        int mid = (l + r) >> 1;
        if (ql <= mid)
            lc->update(ql, qr, x, l, mid);
        if (qr > mid)
            rc->update(ql, qr, x, mid + 1, r);
        maintain();
    }
} pool[N << 2], *curr, *segt;
int m, x, h, a[N];
SegT *build(const int l = 1, const int r = n) {
    if (l == r)
        return new (curr++) SegT(a[l] > x);
    int mid = (l + r) >> 1;
    return new (curr++) SegT(r - l + 1, build(l, mid), build(mid + 1, r));
}
bool check() {
    static int i, ret;
    curr = pool;
    segt = build();
    re (i, 0, m) {
        const Query &q = qwq[i];
        ret = segt->query(q.l, q.r);
        if (ret == 0 || ret == q.r - q.l + 1)
            continue;
        if (q.op) {
            segt->update(q.l, q.l + ret - 1, 1);
            segt->update(q.l + ret, q.r, 0);
        } else {
            segt->update(q.l, q.r - ret, 0);
            segt->update(q.r - ret + 1, q.r, 1);
        }
    }
    return segt->query(h, h);
}

int main() {
    static int i, l, r;
    n = io, m = io;
    rep (i, 1, n)
        a[i] = io;
    re (i, 0, m) {
        Query &q = qwq[i];
        q.op = (int)io, q.l = io, q.r = io;
    }
    h = io;
    l = 0, r = n;
    while (r - l > 1) {
        x = (l + r) >> 1;
        (check() ? l : r) = x; // ans > x ?
    }
    io.print(r);
    io.flush(); // ***
    return 0;
}

