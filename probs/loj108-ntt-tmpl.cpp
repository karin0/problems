#include <cstdio>
#include <cmath>
#include <cctype>
#include <algorithm>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))

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

const int N = 333333, mo = 998244353, g = 3; // O(n + m) -> 2^k
ll w[N], winv[N];
int rev[N];
int qpow(ll a, int n) {
    static ll res;
    for (res = 1; n; n >>= 1, a = a * a % mo)
        if (n & 1)
            res = res * a % mo;
    return res;
}
int init(const int n) {
    static int l, k, x, xinv;
    for (k = 0, l = 1; l < n; l <<= 1, ++k);
    x = qpow(g, (mo - 1) / l);  // l here
    xinv = qpow(x, mo - 2);
    w[0] = winv[0] = 1;
    rev[0] = 0;
    for (int i = 1; i < l; ++i) {
        w[i] = w[i - 1] * x % mo;
        winv[i] = winv[i - 1] * xinv % mo;
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
    }
    return l;
}
int mck(const int x) {
    return x >= mo ? x - mo : x;
}
int mck2(const int x) {
    return x < 0 ? x + mo : x;
}
void dft(int *a, const int n) {
    int i, l, m, t;
    for (i = 0; i < n; ++i)
        if (i < rev[i])
            std::swap(a[i], a[rev[i]]);
    for (l = 2; l <= n; l <<= 1) {
        m = l >> 1;
        t = n / l;
        for (int *p = a; p != a + n; p += l)
            for (i = 0; i < m; ++i) {
                int x = w[t * i] * p[m + i] % mo;
                p[m + i] = mck2(p[i] - x);
                p[i] = mck(p[i] + x);
            }
    }
}
void idft(int *a, const int n) {
    std::swap(w, winv);
    dft(a, n);
    std::swap(w, winv);
    ll ninv = qpow(n, mo - 2);
    for (int i = 0; i < n; ++i)
        a[i] = a[i] * ninv % mo;
}
void mul(int *a, int *b, const int l) {
    static int i;
    dft(a, l);
    dft(b, l);
    for (i = 0; i < l; ++i)
        a[i] = (ll)a[i] * b[i] % mo;
    idft(a, l);
}

int main() {
    static int i, n, m, l;
    static int c1[N], c2[N];
    n = io, m = io;
    l = init(n + m);
    
    rep (i, 0, n)
        c1[i] = io;
    rep (i, 0, m)
        c2[i] = io;
    mul(c1, c2, l);
    for (i = 0; i < n + m + 1; ++i) {
        io.print(c1[i], false);
        io.pc(' ');
    }
    io.flush();
    return 0;
}
