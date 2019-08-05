#include <cstdio>
#include <cctype>
#include <algorithm>

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
const int N = 50003;
// Informatik verbindet dich und mich.

typedef long long ll;
int mo;
int phi(int x) {
    static int res, i;
    for (res = x, i = 2; i * i <= x; ++i)
        if (x % i == 0) {
            res = res / i * (i - 1);
            do x /= i; while (x % i == 0);
        }
    if (x > 1)
        res = res / x * (x - 1);
    return res;
}
int seq[N], k, pmo[N];
bool f;
ll pow(ll a, ll x, int m) {
    static ll res;
    for (res = 1, f = false; x; x >>= 1, f |= ((a *= a) >= m && x), a %= m)
        if (x & 1)
            f |= (res *= a) >= m, res %= m;
    return res;
}
int n, c;
int calc(int a, int e) {
    static int i;
    a = a < pmo[e] ? a : a % pmo[e] + pmo[e];
    // if (a >= pmo[e])
    //    a = a % pmo[e] + pmo[e];
    for (i = e - 1; i >= 0; --i) {
        a = pow(c, a, pmo[i]);
        if (f)
            a += pmo[i];
    }
    return a % mo;
}
struct Node {
    Node *lc, *rc;
    int sum, cnt;
    Node() {}
    Node(Node *_lc, Node *_rc) : lc(_lc), rc(_rc) {
        maintain();
    }
    Node(const int _s) : sum(_s) {}
    inline void maintain() {
        sum = lc->sum + rc->sum;
        if (sum >= mo)
            sum -= mo;
        cnt = std::min(lc->cnt, rc->cnt);
    }
    void update(int ql, int qr, int l = 1, int r = n) {
        if (cnt >= k)
            return;
        if (l == r) {
            sum = calc(seq[l], ++cnt);
            return;
        }
        int mid = (l + r) >> 1;
        if (ql <= mid)
            lc->update(ql, qr, l, mid);
        if (qr > mid)
            rc->update(ql, qr, mid + 1, r);
        maintain();
    }
    int query(int ql, int qr, int l = 1, int r = n) {
        if (ql <= l && r <= qr)
            return sum;
        int mid = (l + r) >> 1, res = 0;
        if (ql <= mid)
            res += lc->query(ql, qr, l, mid);
        if (qr > mid)
            res += rc->query(ql, qr, mid + 1, r);
        if (res >= mo)
            res -= mo;
        return res;
    }
} pool[N << 2], *curr = pool, *segt;
Node *build(int l, int r) {
    if (l == r)
        return new (curr++) Node(seq[l] % mo);
    else {
        int mid = (l + r) >> 1;
        return new (curr++) Node(build(l, mid), build(mid + 1, r));
    }
}

int main() {
    static int m, i, opt, l, r;
    n = io, m = io, mo = io, c = io;
    for (i = 1; i <= n; ++i)
        seq[i] = io;
    segt = build(1, n);
    k = 0, pmo[0] = mo;
    while (pmo[k] > 1)
        ++k, pmo[k] = phi(pmo[k - 1]);
    // mo 迭代 k 次后得到 1
    pmo[++k] = 1;
    while (m--) {
        opt = io, l = io, r = io;
        if (opt)
            io.print(segt->query(l, r));
        else
            segt->update(l, r);
    }
    io.flush();
    return 0;
}
