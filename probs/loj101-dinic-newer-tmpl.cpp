#include <cstdio>
#include <cctype>
#include <climits>
#include <algorithm>
#include <queue>
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
const int N = 103, M = 5003, inf = INT_MAX;
namespace g {
    struct Edge;
    struct Node {
        int d;
        struct Edge *e, *c;
    } g[N], *s, *t;
    struct Edge {
        Node *v;
        Edge *e, *r;
        ll c;

        Edge() {}
        Edge(Node *_u, Node *_v, int _c) : v(_v), e(_u->e), c(_c) {
            _u->e = this;
        }
        void *operator new (size_t) {
            static Edge pool[M * 2], *curr = pool;
            return curr++;
        }
    };
    int n;
    void arc(Node *const u, Node *const v, const int c) {
        new Edge(u, v, c);
        new Edge(v, u, 0);
        (u->e->r = v->e)->r = u->e;
    }
    bool bfs() {
        static Node *u, *v;
        std::queue<Node *> q;
        for (u = g + 1; u <= g + n; ++u)
            u->c = u->e, u->d = 0;
        s->d = 1;
        q.push(s);
        while (!q.empty()) {
            u = q.front(), q.pop();
            for (Edge *e = u->e; e; e = e->e)
                if (e->c > 0 && (v = e->v)->d == 0) {
                    v->d = u->d + 1;
                    if (v == t)
                        return true;
                    q.push(v);
                }
        }
        return false;
    }
    ll dfs(Node *const u, ll lim) {
        if (u == t || lim == 0)
            return lim;
        ll res = 0, f;
        Node *v;
        for (Edge *&e = u->c; e; e = e->e)
            if (e->c > 0 && ((v = e->v)->d == u->d + 1) && (f = dfs(v, std::min(e->c, lim))) > 0) {
                e->c -= f;
                e->r->c += f;
                res += f;
                lim -= f;
                if (lim == 0)
                    return res;
            }
        return res;
    }
    ll dinic() {
        static ll res;
        res = 0;
        while (bfs())
            res += dfs(s, inf);
        return res;
    }
}

int main() {
    static int n, m, u, v, c;
    n = io, m = io, u = io, v = io;
    g::n = n;
    g::s = &g::g[u];
    g::t = &g::g[v];
    while (m--) {
        u = io, v = io, c = io;
        g::arc(&g::g[u], &g::g[v], c);
    }
    io.print(g::dinic());
    io.flush(); // ***
    return 0;
}
