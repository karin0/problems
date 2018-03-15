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
const int N = 50002, M = 502;
int ha[15000000], wcnt;
int read_text(int * const a) {
    static char c;
    static int hsh, *p;
    for (p = a; ; ) {
        hsh = 0;
        for (; !islower(c); c = io.gc());
        for (; islower(c); c = io.gc())
            hsh = hsh * 27 + (c - 'a' + 1);
        if (!ha[hsh])
            ha[hsh] = ++wcnt;
        *p++ = ha[hsh];
        if (c != ' ')
            return p - a;
    }
}
int s[N], ta[N], tb[N], tc[N], n, la, lb, lc;
int main() {
    static int ans, i, j, l, r, k, al, ar, cr;
    n = read_text(s);
    la = read_text(ta);
    lb = read_text(tb);
    lc = read_text(tc);
    for (i = j = 0; j < la; ++i)
        if (s[i] == ta[j])
            ++j; // printf("Met %d\n",s[i]);
    for (l = al = i; s[l] != tb[0]; ++l);
    for (i = n - 1, j = lc - 1; j >= 0; --i)
        if (s[i] == tc[j])
            --j; // printf("Met %d\n",s[i]);
    for (cr = ar = i; s[cr] != tb[lb - 1]; --cr);
    for (r = cr; s[r] != tb[0]; --r);
    ans = n;
    rep (i, l, r)
        if (s[i] == tb[0]) {
            for (j = i, k = 0; k < lb && j <= cr; ++j)
                if (s[j] == tb[k])
                    ++k;
            if (k == lb)
                ans = std::min(ans, j - i - lb);
        }
    io.print(ans + al - la + n - ar - 1 - lc);

    io.flush(); // ***
    return 0;
}
