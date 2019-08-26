#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cmath>
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

const int N = 100003;
int n, siz[N];
bool rm[N];
struct Edge {
    int v;
    Edge *e;
} *g[N], pool[N + N], *curr = pool;
void arc(int u, int v) {
    g[u] = new (curr++) Edge{v, g[u]};
    g[v] = new (curr++) Edge{u, g[v]};
}
int cnt;
void dfs1(int u) {
    siz[u] = 1;
    for (Edge *e = g[u]; e; e = e->e) if (!siz[e->v]) {
        dfs1(e->v);
        siz[u] += siz[e->v];
    }
}
void dfs2(int u, int fa) {
    if (rm[u])
        return;
    ++cnt;
    for (Edge *e = g[u]; e; e = e->e) if (e->v != fa) {
        dfs2(e->v, u);
    }
}
int main() {
    static int i, ans;
    n = io;
    re (i, 1, n)
        arc(io, io);
    dfs1(1);
    rep (i, 2, n)
        if ((siz[i] & 1) == 0)
            rm[i] = true, ++ans;
    if (ans == 0) {
        io.print((n & 1) ? -1 : 0);
        io.flush();
        return 0;
    }
    dfs2(1, 0);
    io.print((cnt & 1) ? -1 : ans);

    io.flush();
    return 0;
}
