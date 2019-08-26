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
            x = x * 10 + c - '0';
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
        static int y;
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
        for (; *st; ++st)
            pc(*st);
    }
    inline void flush() {
        fwrite(b, 1, p - b, stdout);
    }
} io;
typedef long long ll;
const int N = 1000003;
int n, m, a[N], b[N];
int main() {
    static int i, j, k;
    static ll sa, sb;
    n = io;
    m = io;
    rep (i, 1, n)
        a[i] = io;
    rep (i, 1, m)
        b[i] = io;
    i = j = 1;
    sa = a[1];
    sb = b[1];
    for (; i <= n && j <= m; ) {
        while (sa == sb) {
            // printf("new at %d, %d sum %lld\n",i,j,sa);
            ++k;
            if (i == n || j == m)
                break;
            ++i, ++j, sa = a[i], sb = b[j];
        }
        if (sa < sb)
            ++i, sa += a[i];
        else
            ++j, sb += b[j];
    }
    io.print(k);
    io.flush(); // ***
    return 0;
}
