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

const int N = 20005;
int n, a[N];
bool check(int x) {
    static int i, fl, fr, fr0;
    fl = fr = a[1];
    rep (i, 2, n) {
        fr0 = fr;
        fr = std::min(a[i], a[1] - fl);
        fl = std::max(0, a[i] - (x - a[i - 1] - a[1] + fr0));
    }
    return fl == 0;
}
int main() {
    static int i, l, r, x;
    n = io;
    rep (i, 1, n)
        a[i] = io;
    if (n == 1) {
        io.print(a[1]);
        io.flush();
        return 0;
    }
    if (!(n & 1)) {
        for (i = 1; i <= n; i += 2)
            l = std::max(l, a[i]);
        for (i = 2; i <= n; i += 2)
            r = std::max(r, a[i]);
        io.print(l + r);
        io.pc('\n');
        io.flush();
        return 0;
    }
    l = a[1] + a[n];
    rep (i, 2, n)
        l = std::max(l, a[i] + a[i - 1]);
    r = l + a[n];
    --l;
    while (r - l > 1) {
        x = (l + r) >> 1;
        (check(x) ? r : l) = x;
    }
    io.print(r);
    io.pc('\n');
    io.flush(); // ***
    return 0;
}
