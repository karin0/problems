#include <cstdio>
#include <cctype>
#include <algorithm>
#include <queue>
#include <map>
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

typedef long long ll;
const int w = 60, N = 50005, M = 100005;
inline bool bit(const ll x, const int k) {
    return (x >> k) & 1ll;
}
namespace basis {
    ll b[w + 1];
    int i;
    void insert(ll x) {
        static int j;
        for (i = w; i >= 0; --i) {
            if (!x)
                return;
            if (!bit(x, i))
                continue;
            if (b[i])
                x ^= b[i];
            else {
                for (j = 0; j < i; ++j)
                    if (bit(x, j))
                        x ^= b[j];
                for (j = i + 1; j <= w; ++j)
                    if (bit(b[j], i))
                        b[j] ^= x;
                b[i] = x;
                return;
            }
        }
    }
    ll calc(ll x) {
        rep (i, 0, w) if (b[i])
            x = std::max(x, x ^ b[i]);
        return x;
    }
}

struct Node {
    ll dep;
    struct Edge *e;
} g[N];
struct Edge {
    Node *v;
    ll w;
    Edge *e;
    Edge() {}
    Edge(Node *_u, Node *_v, ll _w) : v(_v), w(_w), e(_u->e) {
        _u->e = this;
    }
    void *operator new (size_t) {
        static Edge pool[M * 2], *curr = pool;
        return curr++;
    }
};
void dfs(Node *u, Node *f) {
    Node *v;
    for (Edge *e = u->e; e; e = e->e) {
        if ((v = e->v)->dep == -1) {
            v->dep = u->dep ^ e->w;
            dfs(v, u);
        } else if (v != f)
            basis::insert(u->dep ^ v->dep ^ e->w);
    }
}
std::map<int, ll> chk[N];
int main() {
    static int n, m, i, u, v;
    static ll x;  // **********
    static std::map<int, ll>::iterator it;
    n = io;
    m = io;
    rep (i, 1, m) {
        u = io;
        v = io;
        if (u == v) {
            basis::insert(io);
        } else {
            x = io;
            if (u > v)
                std::swap(u, v);
            it = chk[u].find(v);
            if (it != chk[u].end())
                basis::insert(it->second ^ x);
            else {
                new Edge(&g[u], &g[v], x);
                new Edge(&g[v], &g[u], x);
                chk[u][v] = x;
            }
        }
    }
    rep (i, 2, n)
        g[i].dep = -1;
    dfs(&g[1], NULL);
    io.print(basis::calc(g[n].dep));

    io.flush();
    return 0;
}
