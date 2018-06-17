#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
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

const int N = 200004;
int n, m, bin, md, dep[N], jmp[18][N], wmax[18][N], vans[N];
namespace dsu {
    int fa[N];
    void init() {
        static int i;
        rep (i, 0, n)
            fa[i] = i;
    }
    int find(int u) {
        return fa[u] == u ? u : fa[u] = find(fa[u]);
    }
    void unite(int u, int v) { // u -> v
        fa[find(u)] = find(v);
    }
    bool same(int u, int v) {
        return find(u) == find(v);
    }
}
struct Edge {
    int v, w;
    Edge *e;
} pool[N * 2], *curr = pool, *g[N];
void arc(int u, int v, int w) {
    g[u] = new (curr++) Edge{v, w, g[u]};
    g[v] = new (curr++) Edge{u, w, g[v]};
}
void dfs(int u) {
    int v;
    for (Edge *e = g[u]; e; e = e->e) if (!dep[v = e->v]) {   // ********** Never check with fa as root has no fa too
        jmp[0][v] = u; // printf("fa %d = %d\n", v, u);
        wmax[0][v] = e->w;
        md = std::max(md, dep[v] = dep[u] + 1);
        dfs(v);
    }
}
int lca(int u, int v) {
    static int j;
    if (dep[u] < dep[v])
        std::swap(u, v);
    per (j, bin, 0)
        if (dep[jmp[j][u]] >= dep[v])
            u = jmp[j][u];
    if (u == v)
        return u;
    per (j, bin, 0)
        if (jmp[j][u] != jmp[j][v])
            u = jmp[j][u], v = jmp[j][v];
    return jmp[0][u];
}
int query_max(int u, int v) {
    static int dl, j, res;
    dl = dep[lca(u, v)];
    res = 0;
    per (j, bin, 0) {
        if (dep[jmp[j][u]] >= dl) {
            res = std::max(res, wmax[j][u]);
            u = jmp[j][u];
        }
        if (dep[jmp[j][v]] >= dl) {
            res = std::max(res, wmax[j][v]);
            v = jmp[j][v];
        }
    }
    return res;
}
void update(int u, int dv, int w) { // mark on [u, v)
    static int f;
    if (dep[u] <= dv)
        return;   // ******
    while (true) {
        while (vans[u]) {
            f = jmp[0][dsu::find(u)];
            if (dep[f] <= dv)
                return;
            dsu::unite(u, f);
            u = f;
        }
        // for (; vans[u]; f = jmp[0][dsu::find(u)], dsu::unite(u, f), u = f);   // ";" must be at the end
            //printf("At %d f = %d\n", u, dsu::find(u));
        // if (dep[u] <= dv)
        //    return;
        vans[u] = w;
        // if (dsu::find(u) != u)
        //     printf("Damn. find %d = %d\n", u, dsu::find(u));
        f = jmp[0][u];
        if (dep[f] <= dv)
            return;   // ******
        dsu::unite(u, f);
        u = f;
    }
}
struct Pair {
    int u, v, w, *ans;
    bool used;
    bool operator < (const Pair &rhs) const {
        return w < rhs.w;
    }
} qwq[N];
int main() {
    static int i, j, ans[N];
    n = io;
    m = io;
    rep (i, 1, m) {
        Pair &e = qwq[i];
        e.u = io;
        e.v = io;
        e.w = io;
        e.ans = &ans[i];
    }
    std::sort(qwq + 1, qwq + m + 1);
    dsu::init();
    rep (i, 1, m) {
        Pair &e = qwq[i];
        if (!dsu::same(e.u, e.v)) {
            dsu::unite(e.u, e.v);
            arc(e.u, e.v, e.w);
            e.used = true;
        }
    }
    const static int rt = 1;
    dep[rt] = 1;
    dfs(rt);
    bin = floor(log2(md - 1));
    rep (j, 1, bin)
        rep (i, 1, n) {
            jmp[j][i] = jmp[j - 1][jmp[j - 1][i]];
            wmax[j][i] = std::max(wmax[j - 1][i], wmax[j - 1][jmp[j - 1][i]]);
        }
    dsu::init();
    rep (i, 1, m) {
        Pair &e = qwq[i];
        if (!e.used) {
            *e.ans = query_max(e.u, e.v) - 1;
            j = dep[lca(e.u, e.v)];
            update(e.u, j, e.w);
            update(e.v, j, e.w);
        }
    }
    rep (i, 1, m) {
        Pair &e = qwq[i];
        if (e.used)
            *e.ans = vans[dep[e.u] < dep[e.v] ? e.v : e.u] - 1;
    }
    rep (i, 1, m) {
        io.print(ans[i], false);
        io.pc(i == m ? '\n' : ' ');
    }

    io.flush();
    return 0;
}
