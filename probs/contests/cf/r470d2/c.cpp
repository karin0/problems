#include <cstdio>
#include <climits>
#include <algorithm>
#include <new>
#include <cctype>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))
#define news new (alloc(sizeof(SegT)))

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
const int N = 100003;
int n, a[N], t[N], c[N];
ll ext[N], st[N];
// c[i] := (f[i] - f[i - 1]) / 1
// f[i] 
void update(int l, int r) {
    c[l] += 1;
    c[r + 1] -= 1;
}
int main() {
    static int i, j, l, r, x;
    static ll s, tt, pp;
    n = io;
    rep (i, 1, n)
        a[i] = io;
    rep (i, 1, n)
        t[i] = io, st[i] = st[i - 1] + t[i];
    st[n + 1] = st[n];
    rep (i, 1, n) {
        l = i - 1, r = n;
        tt = st[i - 1];
        pp = a[i];
        while (r - l > 1) {
            x = (l + r) >> 1;
            if (st[x] - tt < pp)
                l = x;
            else
                r = x;
        };
        j = l + 1;
        if (st[j] - tt <= pp)
            ++j;
        if (j - 1 >= i)
            update(i, j - 1);
        ext[j] += pp - st[j - 1] + tt;
    }
    rep (i, 1, n) {
        s += c[i];
        io.print(s * t[i] + ext[i]);
        io.pc(i < n ? ' ' : '\n');
    }
    io.flush();
    return 0;
}
