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

const int N = 1000000;
int n, w, fa[N], jmp[21][N], used[N], dep[N];
struct Edge {
    int v;
    Edge *e;
} *g[N], pool[N + N], *curr = pool;
void arc(int u, int v) {
    g[u] = new (curr++) Edge{v, g[u]};
    g[v] = new (curr++) Edge{u, g[v]};
}
void dfs(int u) {
    for (Edge *e = g[u]; e; e = e->e) if (!dep[e->v]) {
        dep[e->v] = dep[u] + 1;
        jmp[0][e->v] = u;
        dfs(e->v);
    }
}
int main() {
    static int k, i, j, u, v, cnt;
    n = io;
    w = floor(log2(n));
    k = n - (int)io; // to keep
    re (i, 1, n)
        arc(io, io);
    dep[n] = 1;
    dfs(n);
    rep (j, 1, w)
        rep (i, 1, n)
            jmp[j][i] = jmp[j - 1][jmp[j - 1][i]];
    used[n] = used[0] = true;
    for (i = n - 1, cnt = 1; i >= 1 && cnt < k; --i) {
        if (used[i])
            continue;
        u = i;
        per (j, w, 0)
            if (!used[jmp[j][u]])
                u = jmp[j][u];
        if (cnt + dep[i] - dep[u] + 1 > k)
            continue;
        used[u] = true;
        for (v = i; v != u; v = jmp[0][v])
            used[v] = true;
        cnt += dep[i] - dep[u] + 1;
    }
    static bool flag = false;
    rep (i, 1, n)
        if (!used[i]) {
            if (flag)
                io.pc(' ');
            else
                flag = true;
            io.print(i, false);
        }

    io.pc('\n');

    io.flush();
    return 0;
}
