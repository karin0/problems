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

const int N = 500003;
struct Node {
    double p, f, g;
    std::vector<struct Edge *> e;
} g[N];
struct Edge {
    Node *v;
    double p;
    Edge() {}
    Edge(Node *_v, const double _p) : v(_v), p(_p) {}
} pool[N * 2], *curr = pool;
int n;
void arc(Node *u, Node *v, const double p) {
    u->e.push_back(new (curr++) Edge(v, p));
    v->e.push_back(new (curr++) Edge(u, p));
}
void dfs1(Node *u, Node *fa) {
    u->f = 1 - u->p;
    Edge *e;
    for (std::vector<Edge *>::iterator it = u->e.begin(); it != u->e.end(); ++it) if ((e = *it)->v != fa) {
        dfs1(e->v, u);
        u->f *= 1 - e->p + e->p * e->v->f;
    }
}
void dfs2(Node *u, Node *fa) {
    Edge *e;
    for (std::vector<Edge *>::iterator it = u->e.begin(); it != u->e.end(); ++it) if ((e = *it)->v != fa) {
        e->v->g = 1 - e->p + e->p * u->f * u->g / (1 - e->p + e->p * e->v->f);
        dfs2(e->v, u);
    }
}
int main() {
    static int i;
    static Node *rt = g + 1;
    static double ans;
    n = io;
    re (i, 1, n) {
        static int u, v;
        u = io;
        v = io;
        arc(&g[u], &g[v], (int)io / (double)100);
    }
    rep (i, 1, n)
        g[i].p = (int)io / (double)100;
    dfs1(rt, NULL);
    rt->g = 1;
    dfs2(rt, NULL);
    rep (i, 1, n)
        ans += g[i].f * g[i].g;
    printf("%.6f\n", n - ans);

    return 0;
}
