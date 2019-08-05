#include <cstdio>
#include <cctype>
#include <algorithm>
#include <climits>
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
typedef long long ll;
const int N = 100003, MAX_DIV_COUNT = 40;
int n, a[N];
struct SegT {
    ll sum, min, ta;
    int len, dcnt;
    SegT *lc, *rc;

    SegT () {}
    SegT (const int _v) : sum(_v), min(_v), ta(0), len(1) {}
    SegT (const int _l, SegT * const _lc, SegT * const _rc) : ta(0), len(_l), lc(_lc), rc(_rc) {
        maintain();
    }
    void *operator new (size_t) {
        static SegT pool[N << 2], *curr = pool;
        return curr++;
    }
    inline void maintain() {
        sum = lc->sum + rc->sum;
        min = std::min(lc->min, rc->min);
    }
    inline void cover_add(const ll x) {
        sum += x * len;
        min += x;
        ta += x;
    }
    inline void push_down() {
        if (ta != 0) {
            lc->cover_add(ta);
            rc->cover_add(ta);
            ta = 0;
        }
    }
    inline void update_add(const int ql, const int qr, const int x, const int l = 1, const int r = n) {
        if (ql <= l && r <= qr) {
            cover_add(x);
            return;
        }
        push_down();
        int mid = (l + r) >> 1;
        if (ql <= mid)
            lc->update_add(ql, qr, x, l, mid);
        if (qr > mid)
            rc->update_add(ql, qr, x, mid + 1, r);
        maintain();
    }
    inline void update_div(const int ql, const int qr, const int x, const int l = 1, const int r = n) {
        if (ql <= l && r <= qr) {
            if (dcnt >= MAX_DIV_COUNT)
                return;
            ++dcnt;
            if (l == r) {
                sum /= x;
                min = sum;
                return;
            }
            push_down();
            int mid = (l + r) >> 1;
            lc->update_div(ql, qr, x, l, mid);
            rc->update_div(ql, qr, x, mid + 1, r);
            maintain();
            return;
        }
        push_down();
        int mid = (l + r) >> 1;
        if (ql <= mid)
            lc->update_div(ql, qr, x, l, mid);
        if (qr > mid)
            rc->update_div(ql, qr, x, mid + 1, r);
        maintain();
    }
    inline ll query_sum(const int ql, const int qr, const int l = 1, const int r = n) {
        if (ql <= l && r <= qr)
            return sum;
        push_down();
        int mid = (l + r) >> 1;
        ll res = 0;
        if (ql <= mid)
            res += lc->query_sum(ql, qr, l, mid);
        if (qr > mid)
            res += rc->query_sum(ql, qr, mid + 1, r);
        return res;
    }
    inline ll query_min(const int ql, const int qr, const int l = 1, const int r = n) {
        if (ql <= l && r <= qr)
            return min;
        push_down();
        int mid = (l + r) >> 1;
        ll res = LLONG_MAX;
        if (ql <= mid)
            res = std::min(res, lc->query_min(ql, qr, l, mid));
        if (qr > mid)
            res = std::min(res, rc->query_min(ql, qr, mid + 1, r));
        return res;
    }
} *segt;
SegT *build(const int l = 1, const int r = n) {
    if (l == r)
        return new SegT(a[l]);
    int mid = (l + r) >> 1;
    return new SegT(r - l + 1, build(l, mid), build(mid + 1, r));
}
int main() {
    static int m, i, op, l, r;
    n = io, m = io;
    rep (i, 1, n)
        a[i] = io;
    segt = build();
    re (i, 0, m) {
        printf("Do %d\n", i);
        op = io, l = io, r = io;
        ++l, ++r;
        if (op == 1)
            segt->update_add(l, r, io);
        else if (op == 2)
            segt->update_div(l, r, io);
        else if (op == 3)
            io.print(segt->query_min(l, r));
        else
            io.print(segt->query_sum(l, r));
    }
    io.flush(); // ***
    return 0;
}

