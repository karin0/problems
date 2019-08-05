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
        return s == t ? -1 : *s++;
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
    void print(T x) {
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
    }
    void puts(const char *st) {
        while (*st)
            pc(*st++);
    }
    inline void flush() {
        fwrite(b, 1, p - b, stdout);
    }
} io;
typedef long long ll;
const int Q = 500003, N = 1000003, mo = 1000000007;
ll fac[N], inv[N], facinv[N], d[N];
void init(int n) {
    static int i;
    fac[0] = 1;
    rep (i, 1, n)
        fac[i] = fac[i - 1] * i % mo;
    inv[1] = 1;
    rep (i, 2, n)
        inv[i] = (mo - mo / i) * inv[mo % i] % mo;
    facinv[0] = 1;
    rep (i, 1, n)
        facinv[i] = facinv[i - 1] * inv[i] % mo;
    d[0] = 1, d[1] = 0, d[2] = 1;
    rep (i, 3, n)
        d[i] = (i - 1) * (d[i - 1] + d[i - 2]) % mo;
}
ll comb(int n, int m) {
    if (m == 0)
        return 1; // *
    if (n == m)
        return 1;
    return fac[n] * facinv[m] % mo * facinv[n - m] % mo;
}

int main() {
    static struct Query {
        int n, m;
    } qwq[Q];
    static int p, i, n, m, mn;
    p = io;
    re (i, 0, p) {
        n = io, m = io;
        if (n >= m)
            mn = std::max(mn, n);
        qwq[i].n = n, qwq[i].m = m;
    }
    init(mn);
    re (i, 0, p) {
        n = qwq[i].n, m = qwq[i].m;
        if (n < m)
            io.pc('0');
        else if (n == m)
            io.pc('1');
        else
            io.print(comb(n, m) * d[n - m] % mo);
        io.pc('\n');
    }

    io.flush(); // ***
    return 0;
}
