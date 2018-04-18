#include <cstdio>
#include <cctype>
#include <cstring>
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

inline void chmin(int &x, const int v) {
    x = std::min(x, v);
}
const int N = 1002;
int n, a[N], b[N], dmax, off, _f[N * 10 + 100], _g[N * 10 + 100], inf = 0x7f7f7f7f, *f, *g;
int main() {
    static int i, j, x, y;
    off = (dmax = 5 * (n = io)) + 10;
    f = _f + off;
    g = _g + off;
    rep (i, 1, n) {
        a[i] = io;
        b[i] = io;
    }
    memset(_f, 0x7f, sizeof(_f));
    memset(_g, 0x7f, sizeof(_g));
    f[0] = 0;
    rep (i, 1, n) {
        std::swap(_f, _g);
        rep (j, -dmax, dmax) {
            f[j] = inf; // ***
            chmin(f[j], g[j - (a[i] - b[i])]);
            chmin(f[j], g[j - (b[i] - a[i])] + 1);
        }
    }
    rep (j, 0, dmax) {
        x = f[j];
        y = f[-j];
        if (x < inf || y < inf) {
            io.print(std::min(x, y));
            break;
        }
    }

    io.flush();
    return 0;
}
