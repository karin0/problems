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

typedef long long ll;
const int N = 3000004, p = 1000000007;
ll fac[N], facinv[N];
ll pow(ll n, int k) {
    static ll res;
    for (res = 1; k; n = n * n % p, k >>= 1)
        if (k & 1)
            res = res * n % p;
    return res;
}
void init(const int n) {
    static int i;
    fac[0] = 1;
    rep (i, 1, n)
        fac[i] = fac[i - 1] * i % p;
    facinv[n] = pow(fac[n], p - 2);
    per (i, n - 1, 0)
        facinv[i] = facinv[i + 1] * (i + 1) % p;
}
inline int f(const int n, const int k) { // comb(n + k, k) 
    if (n < 0)
        return 0;
    if (n == 0)
        return 1;
    return fac[n + k] * facinv[k] % p * facinv[n] % p;
}
inline void upd(int &x, const int v) {
    x += v;
    if (x >= p)
        x -= p;
}
int calc(const int n, int m) {
    static int i, res, r, t;
    if (n == 0 || m == 0)
        return 0;
    res = 1;
    rep (i, 2, m) {
        t = n - i;
        r = f(t >> 1, i - 1);
        upd(res, r);
        if (t & 1)
            upd(res, r);
        else
            upd(res, f((t - 1) >> 1, i - 1));
    }
    return res;
}

int main() {
    static int n, m;
    n = io;
    m = std::min(n, (int)io);
    init((n >> 1) + m);
    io.print(calc(n, m));
    io.flush(); // ***
    return 0;
}
