#include <cstdio>
#include <cctype>
#include <climits>
#include <algorithm>
#include <queue>
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

const int N = 204, inf = INT_MAX;
namespace g {
    struct Edge;
    struct Node {
        int d;
        struct Edge *e, *c;
    } g[N + N], *s, *t;
    struct Edge {
        Node *v;
        Edge *e, *r;
        int c;

        Edge() {}
        Edge(Node *_u, Node *_v, int _c) : v(_v), e(_u->e), c(_c) {
            _u->e = this;
        }
    } pool[(N + N + N * N) * 2], *curr = pool;
    int n;
    Edge *arc(Node *const u, Node *const v, const int c) {
        new (curr++) Edge(u, v, c);
        new (curr++) Edge(v, u, 0);
        return (u->e->r = v->e)->r = u->e;
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
    int dfs(Node *const u, int lim) {
        if (u == t || lim == 0)
            return lim;
        int res = 0, f;
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
    int dinic() {
        static int res;
        res = 0;
        while (bfs())
            res += dfs(s, inf);
        return res;
    }
    int i;
    void reset() {
        curr = pool;
        rep (i, 1, n)
            g[i].e = NULL;
    }
    Edge *ocurr, *oe[N + N];
    void record() {
        ocurr = curr;
        rep (i, 1, n)
            oe[i] = g[i].e;
    }
    void recover() {
        curr = ocurr;
        rep (i, 1, n)
            g[i].e = oe[i];
    }
    Edge *ocurr1, *oe1[N + N];
    void record1() {
        ocurr1 = curr;
        rep (i, 1, n)
            oe1[i] = g[i].e;
    }
    void recover1() {
        curr = ocurr1;
        rep (i, 1, n)
            g[i].e = oe1[i];
    }
}

int n, m, c, b[N], h[N], fwd[N], r1[N], r2[N];
std::vector<int> a[N][N];
g::Edge *key[N + N];
int main() {
    static int ks, kc, i, j, k, x;
    static std::vector<int>::iterator it, ed;
    ks = io;
    c = io;
    rep (kc, 1, ks) {
        n = io;
        m = io;
        g::n = n + m + 2;
        g::s = &g::g[g::n - 1];
        g::t = &g::g[g::n];
        if (kc > 1) {
            g::reset();
            rep (i, 1, n)
                rep (j, 1, m)
                    a[i][j].clear();
        }
        rep (i, 1, m)
            key[n + i] = g::arc(&g::g[n + i], g::t, b[i] = io);
        rep (i, 1, n)
            rep (j, 1, m)
                if (x = io)
                    a[i][x].push_back(j);
        rep (i, 1, n) {
            h[i] = io;
            key[i] = g::arc(g::s, &g::g[i], 1);
        }
        g::record1();
        rep (i, 1, n) {
            rep (j, 1, m) {
                ed = a[i][j].end();
                for (it = a[i][j].begin(); it != ed; ++it)
                    g::arc(&g::g[i], &g::g[n + *it], 1);
                if (g::dinic())
                    break;
            }
            io.print(fwd[i] = j, false);
            io.pc(i == n ? '\n' : ' ');
        }
        rep (i, 1, n) {
            if (fwd[i] <= h[i])
                io.pc('0');
            else {
                static bool suc;
                suc = false;
                rep (j, 1, h[i]) {
                    ed = a[i][j].end();
                    for (it = a[i][j].begin(); it != ed; ++it)
                        if (b[*it] > 0) {
                            suc = true;
                            break;
                        }
                    if (suc)
                        break;
                }
                if (suc) {
                    g::recover1();
                    rep (j, 1, n) {
                        key[j]->c = 1;
                        key[j]->r->c = 0;
                    }
                    rep (j, 1, m) {
                        key[n + j]->c = b[j];
                        key[n + j]->r->c = 0;
                    }
                    re (j, 1, i - 1) {
                        if (fwd[j] > m)
                            continue;
                        ed = a[j][fwd[j]].end();
                        for (it = a[j][fwd[j]].begin(); it != ed; ++it)
                            g::arc(&g::g[j], &g::g[n + *it], 1);
                        g::dinic();
                        g::record();
                        rep (k, 1, m) {
                            r1[k] = key[n + k]->c;
                            r2[k] = key[n + k]->r->c;
                        }
                        rep (k, 1, h[i]) {
                            ed = a[i][k].end();
                            for (it = a[i][k].begin(); it != ed; ++it)
                                g::arc(&g::g[i], &g::g[n + *it], 1);
                        }
                        if (!g::dinic()) {
                            io.print(i - j, false);
                            break;
                        }
                        g::recover();
                        key[i]->c = 1;
                        key[i]->r->c = 0;
                        rep (k, 1, m) {
                            key[n + k]->c = r1[k];
                            key[n + k]->r->c = r2[k];
                        }
                    }
                    if (j == i - 1)
                        io.pc('1');
                } else
                    io.print(i, false);
            }
            io.pc(i == n ? '\n' : ' ');
        }
    }
    io.flush();
    return 0;
}
