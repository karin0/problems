#include <cstdio>
#include <cctype>
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

const int N = 10004;
struct Node {
    int dis;
    bool ins;
    struct Edge *e;
} g[N];
struct Edge {
    Node *v;
    int w;
    Edge *e;
    
    Edge() {}
    /*
    Edge(Node *_u, Node *_v, int _w) : v(_v), w(_w), e(_u->e) {
        _u->e = this;
    }*/
    Edge(Node *_u, Node *_v, int _w) : v(_v), w(_w), e(_u->e) {
        _u->e = this;
    }
    void *operator new (size_t) {
        static Edge pool[N << 1], *curr = pool;
        return curr++;
    }
};
int n;
bool flag;
void spfa(Node *const u) {
    Node *v;
    int t;
    u->ins = true;
    for (Edge *e = u->e; e; e = e->e) {
        v = e->v;
        t = u->dis + e->w;
        if (v->dis > t) {
            if (v->ins) {
                flag = true;
                return;
            }
            v->dis = t;
            spfa(v);
            if (flag)
                return;
        }
    }
    u->ins = false;
}
int main() {
    static int i, m, op, u, v;
    n = io, m = io;
    rep (i, 1, m) {
        op = io, u = io, v = io;
        if (op == 1)
            new Edge(&g[u], &g[v], -(int)io);
        else if (op == 2)
            new Edge(&g[v], &g[u], io);
        else
            new Edge(&g[u], &g[v], 0), new Edge(&g[v], &g[u], 0);
    }
    rep (i, 1, n) {
        spfa(&g[i]);
        if (flag) {
            io.ps("No");
            io.flush();
            return 0;
        }
    }
    io.ps("Yes");
    io.flush(); // ***
    return 0;
}
