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

const int N = 333333; // O(n + m) -> 2^k
const double pi = acos(-1.0);
// typedef std::complex<double> comp;
struct comp {
    double re, im;
    comp() {}
    comp(double _r, double _i) : re(_r), im(_i) {}
    comp operator + (const comp &b) const {
        return comp(re + b.re, im + b.im);
    }
    comp &operator += (const comp &b) {
        return *this = *this + b;
    }
    comp operator - (const comp &b) const {
        return comp(re - b.re, im - b.im);
    }
    comp operator * (const comp &b) const {
        return comp(re * b.re - im * b.im, re * b.im + im * b.re);
    }
    comp &operator *= (const comp &b) {
        return *this = *this * b;
    }
    template <class T>
    comp &operator = (const T &b) {
        return *this = comp(b, 0);
    }
    comp conj() const {
        return comp(re, -im);
    }
} w[N], winv[N];
int rev[N];
int init(const int n) {
    static int l, k;
    for (k = 0, l = 1; l < n; l <<= 1, ++k);
    for (int i = 0; i < l; ++i) {
        w[i] = comp(cos(2 * pi / l * i), sin(2 * pi / l * i));
        winv[i] = w[i].conj();
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
    }
    return l;
}
void dft(comp *a, const int n) {
    int i, l, m, t;
    for (i = 0; i < n; ++i)
        if (i < rev[i])
            std::swap(a[i], a[rev[i]]);
    for (l = 2; l <= n; l <<= 1) {
        m = l >> 1;
        t = n / l;
        for (comp *p = a; p != a + n; p += l)
            for (i = 0; i < m; ++i) {
                comp x = w[t * i] * p[m + i];
                p[m + i] = p[i] - x;
                p[i] += x;
            }
    }
}
void idft(comp *a, const int n) {
    std::swap(w, winv);
    dft(a, n);
    std::swap(w, winv);
    for (int i = 0; i < n; ++i)
        a[i].re /= n;
}
void mul(comp *a, comp *b, const int l) {
    static int i;
    dft(a, l);
    dft(b, l);
    for (i = 0; i < l; ++i)
        a[i] *= b[i];
    idft(a, l);
}

int main() {
    static int i, n, m, l, f[N], g[N];
    static comp c1[N], c2[N];
    n = io, m = io;
    l = init(n + m);
    
    rep (i, 0, n)
        f[i] = io, c1[i].re = f[i];
    rep (i, 0, m)
        g[i] = io, c2[i].re = g[i];
    mul(c1, c2, l);
    for (i = 0; i < n + m + 1; ++i) {
        io.print((int)floor(c1[i].re + 0.5), false);
        io.pc(' ');
    }
    io.flush();
    return 0;
}
