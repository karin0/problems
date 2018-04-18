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

const int N = 102, E = 4, inf = 0x3f3f3f3f;
int n, m, a[N], b[N], diff[5][5] = {
    { 5, -1, -2, -1, -3},
    {-1,  5, -3, -2, -4},
    {-2, -3,  5, -2, -2},
    {-1, -2, -2,  5, -1},
    {-3, -4, -2, -1,  5}
};
inline int num(const char c) {
    switch (c) {
        case 'A': return 0;
        case 'C': return 1;
        case 'G': return 2;
        default:  return 3;
    }
}
int main() {
    static int i, j, f[N], g[N], ai, deai;
    static char s[N];
    n = io;
    io.gs(s + 1);
    rep (i, 1, n)
        a[i] = num(s[i]); // printf("a[%d] = %d   %d\n", i, a[i], diff[0][2]);
    m = io;
    io.gs(s + 1);
    rep (i, 1, m)
        b[i] = num(s[i]); // printf("b[%d] = %d\n", i, b[i]);
    rep (j, 1, m)
        f[j] = f[j - 1] + diff[E][b[j]];
    rep (i, 1, n) {
        std::swap(f, g);
        deai = diff[E][ai = a[i]];
        f[0] = g[0] + deai;
        rep (j, 1, m)
            f[j] = std::max(g[j - 1] + diff[ai][b[j]], std::max(f[j - 1] + diff[E][b[j]], g[j] + deai));
    }
    io.print(f[m]);
    io.flush();
    return 0;
}
