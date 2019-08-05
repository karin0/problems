#include <cstdio>
#include <cctype>
#include <algorithm>
#include <stack>
#include <queue>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))
#include <iostream>
#define out(x) std::cerr << #x << " = " << x << std::endl
 // #define out(x) 0

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

const int N = 50003, M = 100003;

int n;
namespace g {
    template <class T>
    struct Edge {
        T *v;
        Edge<T> *e;
        Edge<T>() {}
        Edge<T>(T *_u, T *_v) : v(_v), e(_u->e) {
            _u->e = this;
        }
    };
    /* struct SCC {
        SCC *opp;
        int ind, mark;
        Edge<SCC> *e;
    } scc[N * 2]; */
    struct Node {
        int dfn, low, bel;
        bool ins;
        // SCC *bel;
        Edge<Node> *e;
    } g[N * 2];
    Edge<Node> pool[M * 2], *curr = pool;
    int cv, tim, cs;
    void arc(int i, int j) {
        new (curr++) Edge<Node>(&g[i], &g[j]);
    }
    /* Edge<SCC> spool[M * 2], *scurr = spool;
    void arc(SCC *u, SCC *v) {
        new (scurr++) Edge<SCC> (u, v);
    } */
    void cstr(int i, bool hi, int j, bool hj) {
        arc(hi ? n + i : i, hj ? n + j : j);
        arc(hj ? j : n + j, hi ? i : n + i);
    }
    std::stack<Node *> sta;
    void tarjan(Node *u) {
        u->low = u->dfn = ++tim;
        sta.push(u);
        u->ins = true;
        Node *v;
        for (Edge<Node> *e = u->e; e; e = e->e) {
            v = e->v;
            if (!v->dfn)  // *************
                tarjan(v), u->low = std::min(u->low, v->low);
            else if (v->ins)
                u->low = std::min(u->low, v->dfn);
        }
        if (u->dfn == u->low) {
            ++cs;
            do {
                v = sta.top();
                sta.pop();
                v->ins = false;
                v->bel = /* &scc[cs] */ cs;
            } while (u != v);
        }
    }
    /*
    void mark(SCC *u) {
        if (u->mark != -1)
            return;
        u->mark = 0;
        for (Edge<SCC> *e = u->e; e; e = e->e)
            mark(e->v);
    }
    std::queue<SCC *> q;*/
    bool build() {
        static int i;
        rep (i, 1, cv)
            if (!g[i].dfn)   // *********
                tarjan(&g[i]);
        rep (i, 1, n) {
            if (g[i].bel == g[n + i].bel)
                return false;
            //g[i].bel->opp = g[n + i].bel;
            //g[n + i].bel->opp = g[i].bel;
        }
        /*
        rep (i, 1, cv) {
            static SCC *su;
            su = g[i].bel;
            for (Edge<Node> *e = g[i].e; e; e = e->e)
                if (e->v->bel != su)  // *****
                    arc(e->v->bel, su), ++su->ind;
        }
        rep (i, 1, cs) {
            scc[i].mark = -1;
            if (scc[i].ind == 0)
                q.push(&scc[i]);
        }
        while (!q.empty()) {
            static SCC *u;
            u = q.front();
            q.pop();
            if (u->mark != -1)
                continue;  // ********
            u->mark = 1;
            mark(u->opp);
            for (Edge<SCC> *e = u->e; e; e = e->e)
                if (--e->v->ind == 0)
                    q.push(e->v);
        }*/
        return true;
    }
    bool res(int i) {
        // out(i);
        // out(scc[n + i].mark);
        // return scc[n + i].mark;
        return g[i].bel > g[n + i].bel;
    }
    void reset() {
        static int i;
        tim = cs = 0;  // **********
        curr = pool;
        // scurr = spool;
        rep (i, 1, cv) {   // ************** cv, not n
            g[i].dfn = 0;
            g[i].ins = false;
            g[i].e = NULL;
        } /*
        rep (i, 1, cs) {
            scc[i].ind = 0;
            scc[i].e = NULL;
        }*/
    }
}
int main() {
    static int d, m, xs[12], cnt, csn, uni, i;
    static char s[N], csn0[6] = {'B', 'A', 'A'}, csn1[6] = {'C', 'C', 'B'};
    static struct CSTR {
        int i, j;
        char hi, hj;
    } qwq[M];
    n = io;
    g::cv = n << 1;
    d = io;
    io.gs(s + 1);
    m = io;
    re (i, 0, m) {
        static char t[4];
        CSTR &q = qwq[i];
        q.i = io;
        io.gs(t);
        q.hi = t[0];
        q.j = io;
        io.gs(t);
        q.hj = t[0];
    }
    rep (i, 1, n)
        if (s[i] == 'x')
            xs[cnt++] = i;
    uni = (1 << d) - 1;
    for (csn = 0; ; ++csn) {
        // out(csn);
        static bool t;
        re (i, 0, d)
            s[xs[i]] = (csn >> i & 1) ? 'a' : 'b';
        re (i, 0, m) {
            CSTR &q = qwq[i];
            if (s[q.i] == tolower(q.hi))
                continue;  // *********
            if (s[q.j] == tolower(q.hj)) {
                t = q.hi == csn1[s[q.i] - 'a'];
                g::cstr(q.i, t, q.i, !t);
            } else
                g::cstr(q.i, q.hi == csn1[s[q.i] - 'a'], q.j, q.hj == csn1[s[q.j] - 'a']);
        }
        if (g::build()) {
            rep (i, 1, n)
                io.pc((g::res(i) ? csn1 : csn0)[s[i] - 'a']); // out(i), out(g::res(i));
            io.pc('\n');
            break;
        }
        if (csn == uni) {
            io.ps("-1");
            break;
        }
        g::reset();
    }

    io.flush();
    return 0;
}
