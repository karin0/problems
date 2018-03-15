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
        return *s++;
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
    inline void flush() {
        fwrite(b, 1, p - b, stdout);
    }
} io;

typedef long long ll;
const int N = 100003;
struct Mat {
    ll a, b, c, d;
    Mat() {}
    Mat(ll _a, ll _b, ll _c, ll _d) : a(_a), b(_b), c(_c), d(_d) {}
    inline Mat operator * (const Mat &rhs) const {
        return Mat(a + b * rhs.a, b * rhs.b, c + d * rhs.a + rhs.c, d * rhs.b + rhs.d);
    }
    inline void make_unit() {
        a = c = d = 0;
        b = 1;
    }
    inline bool is_unit() const {
        return a == 0 && b == 1 && c == 0 && d == 0;
    }
};
int n;
struct Node {
    int len;
    ll sum, old;
    Mat tag;
    Node *lc, *rc;
    Node() {}
    Node(int _len, Node *_lc, Node *_rc) : len(_len), lc(_lc), rc(_rc) {
        tag.make_unit();
        if (lc)
            maintain();
    }
    inline void maintain() {
        sum = lc->sum + rc->sum;
        old = lc->old + rc->old;
    }
    inline void cover(const Mat &x) {
        old = x.c * len + x.d * sum + old;
        sum = x.a * len + x.b * sum;
        tag = x * tag; // ***
    }
    inline void push_down() {
        if (!tag.is_unit()) {
            lc->cover(tag);
            rc->cover(tag);
            tag.make_unit();
        }
    }
    void update(const int ql, const int qr, const Mat &x, const int l = 1, const int r = n)  {
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
    ll query(const int ql, const int qr, const int l = 1, const int r = n) {
        if (ql <= l && r <= qr)
            return old;
        push_down();
        int mid = (l + r) >> 1;
        ll res = 0;
        if (ql <= mid)
            res += lc->query(ql, qr, l, mid);
        if (qr > mid)
            res += rc->query(ql, qr, mid + 1, r);
        return res;
    }
} pool[N << 2], *segt, *curr = pool;
Node *build(const int l, const int r) {
    if (l == r)
        return new (curr++) Node(1, NULL, NULL);
    int mid = (l + r) >> 1;
    return new (curr++) Node(r - l + 1, build(l, mid), build(mid + 1, r));
}
struct Query {
    int l, r;
    ll *ans;
    bool operator < (const Query &rhs) const {
        return r < rhs.r;
    }
} qwq[N];

int main() {
    static int m, i, mono[N], top, a[N], lb[N], cur;
    static ll ans[N];
    n = io, m = io;
    rep (i, 1, n)
        a[i] = io;
    rep (i, 1, n) {
        while (top && a[mono[top]] > a[i]) // **
            --top;
        lb[i] = top ? mono[top] + 1 : 1;
        // printf("lb %d = %d(to %d)\n", i,lb[i],a[lb[i]]);
        mono[++top] = i;
    }
    segt = build(1, n);
    re (i, 0, m) {
        Query &q = qwq[i];
        q.l = io, q.r = io;
        q.ans = &ans[i];
    }
    std::sort(qwq, qwq + m);
    for (i = 1, cur = 0; i <= n && cur < m; ++i) {
        segt->update(lb[i], i, Mat(a[i], 0, 0, 0));
        segt->update(1, i, Mat(0, 1, 0, 1)); // **
        for (; cur < m && qwq[cur].r == i; ++cur) {
            const Query &q = qwq[cur];
            *q.ans = segt->query(q.l, q.r);
        }
    }
    re (i, 0, m)
        io.print(ans[i]);

    io.flush(); // ***
    return 0;
}
