#include <bits/stdc++.h>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))
#ifdef AKARI
    #define ccc(x) std::cerr << #x " = " << x << "  "
    #define cccc(x) std::cerr << #x " = " << x << std::endl
    #define ccccc(x) std::cerr << x << std::endl
#else
    #define ccc(x) 0
    #define cccc(x) 0
    #define ccccc(x) 0
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

const int N = 1003;
int n, m, k, h, cv;
int b[N][N];
struct Pos {
    int x, y;
    Pos() {}
    Pos(int _x, int _y) : x(_x), y(_y) {}
    int bel() {
        return b[x][y];
    }
    bool operator == (const Pos &rhs) const {
        return x == rhs.x && y == rhs.y;
    }
};
struct Item {
    Pos p, q;
    bool fix;
} a[N * N];
struct Node {
    int w;
    bool vis;
    Node *dna;
    Item *atm;
    struct Edge *e;
} g[N * N];
struct Edge {
    Node *v;
    Edge *e;
    Edge() {}
    Edge(Node *s, Node *t) : v(t), e(s->e) {
        s->e = this;
    }
} pool[N * N], *curr = pool;
void arc(int u, int v) {
    new (curr++) Edge(&g[u], &g[v]);
}
void dfs(Node *u) {
    Node *v;
    u->vis = true;
    for (Edge *e = u->e; e; e = e->e) {
        v = e->v;
        if (!v->vis) {
            if (u->w < u->dna->w)
                v->dna = u;
            else
                v->dna = u->dna;
            dfs(v);
        }
    }
}
bool keep[N][N];
int main() {
    static int i, j, x, y;
    static long long ans;
    n = io;
    m = io;
    k = io;
    h = (n * m - 1) / 2;
    cv = h * 2 + 1;
    rep (i, 1, h)
        g[i].w = g[h + i].w = io;
    rep (i, 1, k) {
        x = io;
        keep[x][(int)io] = true;
    }
    rep (i, 1, n) {
        rep (j, 1, n) {
            b[i][j] = x = io;
            if (x) {
                Item &e = a[x];
                if (e.p.x) {
                    e.q = Pos(i, j);
                } else
                    e.p = Pos(i, j);
            }
        }
    }
    rep (i, 1, h) {
        Item &e = a[i];
        if (e.p.x == e.q.x) {
            if (e.p.y > 1) {
                Pos t(e.p.x, e.p.y - 1);
                x = t.bel();
                if (x) {
                    Item &f = a[x];
                    arc(t == f.p ? x : h + x, i);
                } else
                    arc(cv, i);
            }
            if (e.q.y < m) {
                Pos t(e.q.x, e.q.y + 1);
                x = t.bel();
                if (x) {
                    Item &f = a[x];
                    arc(t == f.p ? x : h + x, h + i);
                } else
                    arc(cv, h + i);
            }
        } else {
            if (e.p.x > 1) {
                Pos t(e.p.x - 1, e.p.y);
                x = t.bel();
                if (x) {
                    Item &f = a[x];
                    arc(t == f.p ? x : h + x, i);
                } else
                    arc(cv, i);
            }
            if (e.q.x < n) {
                Pos t(e.q.x + 1, e.q.y);
                x = t.bel();
                if (x) {
                    Item &f = a[x];
                    arc(t == f.p ? x : h + x, h + i);
                } else
                    arc(cv, h + i);
            }

        }
    }
    static Node *rt;
    rt = &g[cv];
    rt->dna = rt;
    dfs(rt);
    rep (i, 1, n)
        rep (j, 1, m)
            if (keep[i][j]) {
                
            }


    io.flush();
    return 0;
}
