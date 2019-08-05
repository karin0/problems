#include <cstdio>
#include <cctype>
#include <algorithm>
#include <vector>
#include <stack>
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

const int N = 100003;
int n;
namespace dsu {
    int fa[N], rk[N], rel[N], ver;
    struct Mod {
        int *x, old;
    } sta[N * 2 * 3];
    inline void mod(int &x, const int v) {
        sta[++ver] = Mod{&x, x};
        x = v;
    }
    void restore(const int s) {
        while (ver > s) {
            *sta[ver].x = sta[ver].old;
            --ver;
        }
    }
    void init() {
        static int i;
        rep (i, 1, n)
            fa[i] = i;
    }
    int find(int x, int &r) {
        r = 0;
        for (; x != fa[x]; x = fa[x])
            r ^= rel[x];
        return x;
    }
    int find(int x) {
        for (; x != fa[x]; x = fa[x]);
        return x;
    }
    inline void unite(int x, int y, const int r) {
        x = find(x);
        y = find(y);
        if (x == y)
            return;
        if (rk[x] > rk[y])
            std::swap(x, y);
        mod(fa[x], y);
        mod(rel[x], r);
        if (rk[x] == rk[y])
            mod(rk[y], rk[y] + 1);
    }
}
struct Edge {
    int u, v, s, t;
};
void solve(const int l, const int r, const std::vector<Edge> &es) {
    std::vector<Edge> les, res;
    int x, y, rx, ry;
    const int mid = (l + r) >> 1, ori = dsu::ver;
    for (std::vector<Edge>::const_iterator it = es.begin(); it != es.end(); ++it) {
        const Edge &e = *it;
        if (e.s <= l && r <= e.t) {
             x = dsu::find(e.u, rx);
             y = dsu::find(e.v, ry);
             if (x != y)
                 dsu::unite(x, y, rx ^ ry ^ 1);
             else if (rx == ry) {
                int i;
                rep (i, l, r)
                    io.ps("No");
                dsu::restore(ori);
                return;
             }
        } else {
            if (e.s <= mid)
                les.push_back(e);
            if (e.t > mid)
                res.push_back(e);
        }
    }
    if (l == r)
        io.ps("Yes");
    else {
        solve(l, mid, les);
        solve(mid + 1, r, res);
    }
    dsu::restore(ori);
    return;
}
int main() {
    static int m, p, i;
    static Edge e;
    static std::vector<Edge> es;
    n = io;
    m = io;
    p = io;
    rep (i, 1, m) {
        e.u = io;
        e.v = io;
        e.s = (int)io + 1;
        e.t = io;
        if (e.s <= e.t)
            es.push_back(e);
    }
    dsu::init();
    solve(1, p, es);

    io.flush();
    return 0;
}
