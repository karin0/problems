#include <cstdio>
#include <cctype>
#include <algorithm>
#include <queue>
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
const int N = 500004;
int n, mx;
struct SegT *nil;
struct SegT {
    SegT *lc, *rc;
    int cnt;
    SegT() {}
    SegT(SegT *const _lc, SegT *const _rc) : lc(_lc), rc(_rc), cnt(_lc->cnt + _rc->cnt) {}
    SegT(const int _c) : lc(nil), rc(nil), cnt(_c) {}
    void *operator new (size_t) {
        static SegT pool[N * 20], *curr = pool;
        return curr++;
    }
    SegT *insert(const int i, const int l = 0, const int r = mx) const {
        if (l == r)
            return new SegT(cnt + 1);
        int mid = (l + r) >> 1;
        if (i <= mid)
            return new SegT(lc->insert(i, l, mid), rc);
        return new SegT(lc, rc->insert(i, mid + 1, r));
    }
    inline int rank() const {
        return lc->cnt;
    }
} *segt[N];
int query_kth(const int l, const int r, int k) {
    static SegT *p, *q;
    static int lb, rb, mid, rk;
    p = l ? segt[l - 1] : nil;
    q = segt[r];
    lb = 0;
    rb = mx;
    while (lb < rb) {
        // printf("Finding %d th in %d, %d\n", k, lb, rb);
        mid = (lb + rb) >> 1;
        rk = q->rank() - p->rank();
        if (k <= rk)
            p = p->lc, q = q->lc, rb = mid;
        else
            p = p->rc, q = q->rc, k -= rk, lb = mid + 1; // ************************************** k -= rk
    }
    // printf("%d th in %d, %d = %d\n", k, l, r, lb);
    return lb;
}
struct Data {
    ll val;
    int i, k;
    Data() {}
    Data(const ll _v, const int _i, const int _k) : val(_v), i(_i), k(_k) {}
    inline bool operator < (const Data &rhs) const {
        return val < rhs.val;
    }
};
std::priority_queue<Data> pq;
int a[N], minl, maxl;
ll sa[N], hash[N];
int main() {
    static int i, k, l, r, _;
    nil = new SegT;
    nil->lc = nil->rc = nil;
    n = io;
    k = io;
    minl = io;
    maxl = io;
    rep (i, 1, n)
        hash[i] = sa[i] = sa[i - 1] + (a[i] = io);
    std::sort(hash, hash + n + 1);
    static ll *end;
    mx = (end = std::unique(hash, hash + n + 1)) - hash - 1;
    segt[0] = nil->insert(sa[0] = std::lower_bound(hash, end, 0) - hash);
    // printf("Ins %lld to segt %d\n", sa[0], 0);
    rep (i, 1, n)
        segt[i] = segt[i - 1]->insert(sa[i] = std::lower_bound(hash, end, sa[i]) - hash);
        // printf("Ins %lld to segt %d\n", sa[i], i);
    pq.push(Data(hash[sa[minl]], minl, 1));
    rep (i, minl + 1, n) {
        l = i - maxl;
        r = i - minl;
        if (l < 0)
            l = 0;
        pq.push(Data(hash[sa[i]] - hash[query_kth(l, r, 1)], i, 1));
    }
    static ll ans;
    for (_ = 1; ; ++_) {
        static Data x;
        x = pq.top();
        ans += x.val;
        if (_ == k)
            break;
        pq.pop();
        i = x.i;
        l = i - maxl;
        r = i - minl;
        if (l < 0)
            l = 0;
        // printf("%d th: i = %d, l = %d, r = %d, k = %d,  K= %d, val = %lld\n", _, i, l, r, x.k, k, x.val);
        if (r - l >= x.k)
            pq.push(Data(hash[sa[i]] - hash[query_kth(l, r, x.k + 1)], i, x.k + 1));
    }
    io.print(ans);
    io.flush(); // ***
    return 0;
}
