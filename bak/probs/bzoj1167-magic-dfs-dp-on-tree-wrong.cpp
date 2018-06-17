#include <cstdio>
#include <cctype>
#include <algorithm>
#include <vector>
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
        return *s++; // return s == t ? -1 : *s++;
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

typedef long long ll;
const int N = 300003, inf = 0x7f7f7f7f;
int w[N], dep[N], f[N], succ[N], sf[N], ssucc[N];
std::vector<int> g[N];
#define adj(u) for (std::vector<int>::iterator it = g[u].begin(); it != g[u].end(); ++it)
void upd(const int u, const int fv, const int sv) {
    if (u == sv)
        return;
    if (fv > f[u] || (fv == f[u] && sv < succ[u]))
        sf[u] = f[u], ssucc[u] = succ[u], f[u] = fv, succ[u] = sv;
    else if (fv > sf[u] || (fv == sf[u] && sv < ssucc[u]))
        sf[u] = fv, ssucc[u] = sv;
}
void dfs1(const int u) {
    int v, fv;
    adj (u) if (!dep[v = *it]) {
        dep[v] = dep[u] + 1;
        dfs1(v);
        upd(u, f[v], succ[v]);
        upd(u, sf[v], ssucc[v]);
        upd(u, w[v] - dep[v], v);
    }
    //   a_v - d(u, v) = a_v - (dep_u + dep_v - 2 * dep_u)
    // = a_v - dep_v + dep_u
}
void dfs2(const int u, const int fa) {
    int v;
    adj (u) if ((v = *it) != fa) {
        upd(v, f[u] - 1, succ[u]);
        upd(v, sf[u] - 1, ssucc[u]);
        upd(v, w[u] - 1, u);
        dfs2(v, u);
    }
}

bool vis[N];
int main() {
    static int n, i, u, v, len, seq[N], tim[N], st;
    static ll m;
    n = io;
    m = io;
    rep (i, 1, n)
        w[i] = io, f[i] = sf[i] = -inf, succ[i] = ssucc[i] = inf;
    re (i, 1, n) {
        u = io, v = io;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dep[1] = 1;
    dfs1(1);
    for (i = 1; i <= n; ++i)
        f[i] += dep[i], sf[i] += dep[i];
    dfs2(1, 0);
    // for (i = 1; i <= n; ++i)
    //    printf("Final succ of %d is %d\n", i, succ[i]);
    for (u = 1; !vis[u]; vis[u] = true, u = succ[u]) {
        tim[u] = len;
        seq[len++] = u;
    }
    i = tim[u];
    if (m <= i)
        io.print(seq[m]);
    else
        io.print(seq[i + (m - i) % (len - i)]);

    io.flush(); // ***
    return 0;
}
