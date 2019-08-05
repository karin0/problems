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

const int N = 253, inf = 0x3f3f3f3f;
int n, m, d[N][N], f[N][N], nid[N], rnid[N], c[N], nc[N];
inline void chmin(int &x, const int v) {
    x = std::min(x, v);
}
inline bool cmp(const int i, const int j) {
    return c[i] < c[j];
}
int main() {
    static int p, i, j, k, u, v;
    n = io;
    m = io;
    p = io;
    rep (i, 1, n) {
        c[i] = io;
        rep (j, 1, n)
            f[i][j] = d[i][j] = inf;
        d[i][i] = 0;
        rnid[i] = i;
    }
    std::sort(rnid + 1, rnid + n + 1, cmp);
    rep (i, 1, n) {
        f[i][i] = nc[i] = c[rnid[i]];
        nid[rnid[i]] = i;
    }
    rep (i, 1, m) {
        u = nid[(int)io];
        v = nid[(int)io];
        chmin(d[u][v], io);
        d[v][u] = d[u][v];
        chmin(f[u][v], d[u][v] + std::max(nc[u], nc[v]));
        f[v][u] = f[u][v];
    }
    rep (k, 1, n) {
        rep (i, 1, n) {
            rep (j, 1, n) {
                chmin(d[i][j], d[i][k] + d[k][j]);
                chmin(f[i][j], d[i][j] + std::max(nc[k], std::max(nc[i], nc[j])));
            }
        }
    }
    while (p--) {
        u = nid[(int)io];
        io.print(f[u][nid[(int)io]]);
    }

    return 0;
}
