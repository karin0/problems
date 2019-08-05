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
            fwrite(p = b, 1, L, stdout);
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

const int N = 502;
int n, m, a[N], b[N], f[N][N], prev[N][N], ans, cnt;
void show(const int i, const int j) {
    if (!f[i][j])
        return;
    printf("i=%d, j=%d\n", i,j);
    if (i > 0 && prev[i][j]) {
        show(i - 1, prev[i][j]);
        if (j && f[i][j] != f[i - 1][prev[i][j]]) {
            ++cnt;
            io.print(b[j]);
            io.pc(cnt < ans ? ' ' : '\n');
        }
    }
}
int main() {
    static int ks, i, j, ai, t, pos, end;
    ks = io;
    while (ks--) {
        memset(f, 0, sizeof(f));
        memset(prev, -1, sizeof(prev));
        n = io;
        rep (i, 1, n)
            a[i] = io;
        m = io;
        rep (i, 1, m)
            b[i] = io;
        rep (i, 1, n) {
            ai = a[i];
            t = pos = 0;
            rep (j, 1, m) {
                if (ai == b[j])
                    f[i][j] = t + 1, prev[i][j] = pos;
                else
                    f[i][j] = f[i - 1][j], prev[i][j] = j;
                if (b[j] < ai && f[i - 1][j] > t)
                    t = f[i - 1][j], pos = j;
            }
        }
        ans = end = 0;
        rep (j, 1, m)
            if (f[n][j] > ans)
                ans = f[n][j], end = j;
        io.print(ans);
        if (ans > 0)
            cnt = 0, show(n, end);
        if (ks)
            io.pc('\n');
    }

    io.flush();
    return 0;
}
