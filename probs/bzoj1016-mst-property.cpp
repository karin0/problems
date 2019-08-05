#include <bits/stdc++.h>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))
#ifdef AKARI
    #define ccc(x) std::cerr << #x " = " << x << "  "
    #define cccc(x) std::cerr << #x " = " << x << std::endl
#else
    #define ccc(x) 0
    #define cccc(x) 0
#endif

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
    void print(T x, const char end = '\n') {
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
        if (end)
            pc(end);
    }
    void ps(const char *st, const char end = '\n') {
        while (*st)
            pc(*st++);
        if (end)
            pc(end);
    }
    inline void flush() const {
        fwrite(b, 1, p - b, stdout); // p = b;
    }
} io;

const int N = 102, M = 1002, mo = 31011;
int n, m, fa[N];
namespace dsu {
    void init() {
        static int i;
        rep (i, 1, n)
            fa[i] = i;
    }
    int find(const int u) {
        return fa[u] == u ? u : fa[u] = find(fa[u]);
    }
    void unite(const int u, const int v) {
        fa[find(u)] = find(v);
    }
    bool same(const int u, const int v) {
        return find(u) == find(v);
    }
}
namespace dsu2 {
    int rk[N], state;
    struct Mod {
        int *x, o;
        Mod() {}
        Mod(int *_x, const int v) : x(_x), o(*_x) {
            *_x = v;
        }
        void restore() {
            *x = o;
        }
    } mods[N * 2];
    void init() {
        static int i;
        state = 0;
        rep (i, 1, n)
            fa[i] = i, rk[i] = 0;
    }
    void mod(int &x, const int v) {
        mods[state++] = Mod(&x, v);
    }
    void restore(const int s) {
        while (state > s)
            mods[--state].restore();
    }
    int find(int u) {
        while (u != fa[u])
            u = fa[u];
        return u;
    }
    void unite(int u, int v) {
        u = find(u);
        v = find(v);
        if (rk[u] > rk[v])
            std::swap(u, v);
        mod(fa[u], v);
        if (rk[u] == rk[v])
            mod(rk[v], rk[v] + 1);
    }
    bool same(const int u, const int v) {
        return find(u) == find(v);
    }
}
struct Edge {
    int u, v, w;
    bool operator < (const Edge &rhs) const {
        return w < rhs.w;
    }
} a[M], b[M];
int main() {
    static int i, cnt, ans = 1;
    n = io;
    m = io;
    re (i, 0, m) {
        Edge &e = a[i];
        e.u = io;
        e.v = io;
        e.w = io;
    }
    std::sort(a, a + m);
    dsu::init();
    re (i, 0, m) {
        Edge &e = a[i];
        ccc(i); ccc(e.u); ccc(e.v); cccc(e.w);
        if (!dsu::same(e.u, e.v)) {
            dsu::unite(e.u, e.v);
            ccc(cnt);
            b[cnt++] = e;
            ccc(e.u); ccc(e.v); cccc(e.w);
        }
    }
    if (cnt != n - 1) {
        io.pc('0');
        io.pc('\n');
        io.flush();
        return 0;
    }
    re (i, 0, m) {
        static int j, cc, cw, cl, cr = -1, res, uni, s, sta;
        static bool succ;
        static Edge *q;
        ++cc;
        if (i == m - 1 || a[i + 1].w != a[i].w) {
            for (cl = cr + 1; cl < cnt && b[cl].w < a[i].w; ++cl);  // judge if cl < cnt *****
            ccc(i); ccc(cl); cccc(cc);
            if (b[cl].w == a[i].w) {
                for (cr = cl + 1; cr < cnt && b[cr].w == a[i].w; ++cr);
                --cr;
                cccc(cr);
                dsu2::init();
                re (j, 0, cl)
                    dsu2::unite(b[j].u, b[j].v);
                re (j, cr + 1, cnt)
                    dsu2::unite(b[j].u, b[j].v);
                sta = dsu2::state;
                uni = 1 << cc;
                cw = cr - cl + 1;
                res = 0;
                q = &a[i - cc + 1];
                for (s = (1 << cw) - 1; s < uni; ++s) if (__builtin_popcount(s) == cw) {
                    succ = true;
                    re (j, 0, cc) if ((s >> j) & 1) {
                        Edge &e = q[j];
                        ccc(j); ccc(e.u); ccc(e.v); cccc("is in");
                        if (dsu2::same(e.u, e.v)) {
                            succ = false;
                            cccc("failed to add");
                            break;
                        }
                        if (j < cc - 1)  // ****** this if shound not be set to break
                            dsu2::unite(q[j].u, q[j].v);
                    }
                    if (succ)
                        ++res;
                    dsu2::restore(sta);   // this should not be skipped
                }
                ccc(res);
                ans = ans * res % mo;
            }
            cc = 0;
        }
    }
    io.print(ans);

    io.flush();
    return 0;
}
