#include <cstdio>
#include <cctype>
#include <algorithm>
#include <queue>
#include <bitset>
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

const int N = 1003, M = 10003;
struct Node {
    int deg;
    std::bitset<1001> d;
    struct Edge *e;
} g[N];
struct Edge {
    Node *v;
    Edge *e;
    Edge() {}
    Edge(Node *_u, Node *_v) : v(_v), e(_u->e) {
        _u->e = this;
    }
} pool[M], *curr = pool;

std::queue<Node *> q;
int main() { // answer should be at the worst case
    static int n, m, i, ans;
    n = io;
    m = io;
    rep (i, 1, m) {
        static int u, v;
        u = io;
        v = io;
        new (curr++) Edge(&g[u], &g[v]);
        ++g[v].deg;
    }
    rep (i, 1, n)
        if (g[i].deg == 0)
            q.push(&g[i]);
    while (!q.empty()) {
        static Node *u, *v;
        static Edge *e;
        u = q.front();
        q.pop();
        ans += u->d.count();
        for (e = u->e; e; e = e->e) {
            v = e->v;
            v->d |= u->d;
            v->d.set(u - g);
            if (--v->deg == 0)
                q.push(v);
        }
    }
    io.print(((n * (n - 1)) >> 1) - ans);

    io.flush();
    return 0;
}
