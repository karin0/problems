#include <bits/stdc++.h>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)
#define pe(i_, s_, t_) for (int i_ = (s_); i_ > (t_); --i_)
#define go(e_, s_) for (Edge *e_ = (s_); e_; e_ = e_->e)
#ifdef AKARI
    void c_() { std::cerr << "\033[39;0m" << std::endl; }
    template<typename T, typename... Args>
    void c_(T a, Args... args) { std::cerr << a << ", "; c_(args...); }
    #define ccc(args...) std::cerr << "\033[32;1m" << #args << "  =  ", c_(args)
    #define ccd(args...) std::cerr << "\033[32;1m", c_(args)
    #define ccf(args...) fprintf(stderr, args)
    #define crep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#else
    #define ccc(...) 0
    #define ccd(...) 0
    #define ccf(...) 0
    #define crep(...) if (false)
#endif
typedef long long ll;
typedef const int cint;
typedef const long long cll;
typedef const char cchar;
#define daze << '\n'

template <cint LI, cint LO>
struct IO {
    char a[LI], b[LO], r[LO], *s, *t, *z, c;
    std::streambuf *fbi, *fbo;
    IO() : z(b) {
        std::ios::sync_with_stdio(false);
        if (LI) std::cin.tie(NULL), fbi = std::cin.rdbuf();
        if (LO) std::cout.tie(NULL), fbo = std::cout.rdbuf();
    }
    ~IO() { if (LO) fbo->sputn(b, z - b); }
    char gc() {
        if (s == t) t = (s = a) + fbi->sgetn(a, LI);
        return s == t ? EOF : *s++;
    }
    template <class T>
    IO &operator >> (T &x) {
        for (c = gc(); c != '-' && !isdigit(c); c = gc());
        bool f = c == '-';
        if (f) c = gc();
        x = c - '0';
        for (c = gc(); isdigit(c); c = gc())
            x = x * 10 + (c - '0');
        if (f) x = -x;
        return *this;
    }
    char *gs(char *x) {
        for (c = gc(); !isgraph(c); c = gc());
        *x++ = c;
        for (c = gc(); isgraph(c); *x++ = c, c = gc());
        return *x = 0, x;
    }
    IO &operator >> (char *x) {
        for (c = gc(); !isgraph(c); c = gc());
        *x++ = c;
        for (c = gc(); isgraph(c); *x++ = c, c = gc());
        return *x = 0, *this;
    }
    IO &operator >> (char &x) {
        for (x = gc(); !isgraph(x); x = gc());
        return *this;
    }
    template <class T>
    operator T () { T x; *this >> x; return x; }
    void pc(cchar x) {
        if (z == b + LO) fbo->sputn(z = b, LO);
        *z++ = x;
    }
    void fl() {
        fbo->sputn(b, z - b);
        z = b;
    }
    template <class T>
    IO &operator << (T x) {
        if (x == 0) return pc('0'), *this;
        if (x < 0) pc('-'), x = -x;
        T y; char *j = r;
        for (; x; x = y) y = x / 10, *j++ = x - y * 10 + '0';
        while (j != r) pc(*--j);
        return *this;
    }
    IO &operator << (char *x) {
        while (*x) pc(*x++);
        return *this;
    }
    IO &operator << (cchar *x) {
        while (*x) pc(*x++);
        return *this;
    }
    IO &operator << (cchar x) { return pc(x), *this; }
};
IO<1000000, 1000000> io;

cint N = 1000003;

int n, a[N];
struct Node {
    int dl, dr;
    struct Edge *e;
} g[N];
struct Edge {
    Node *v;
    Edge *e;
    Edge(Node *s, Node *t) : v(t), e(s->e) {
        s->e = this;
    }
    Edge() {}
};
void arc(Node *const u, Node *const v) {
    static Edge pool[N * 2], *curr = pool;
    new (curr++) Edge(u, v);
    new (curr++) Edge(v, u);
}
void dfs(Node *const u, Node *const fa) {
    static int tim;
    u->dl = ++tim;
    go (e, u->e) if (e->v != fa)
        dfs(e->v, u);
    u->dr = tim;
}
namespace bit {
    ll c[N];
    void add(int i, cint x) {
        for (; i <= n; i += (i & -i))
            c[i] += x;
    }
    ll query(int i) {
        ll res = 0;
        for (; i; i -= (i & -i))
            res += c[i];
        return res;
    }
    inline ll query(cint l, cint r) {
        return query(r) - query(l - 1);
    }
}
int main() {
    int m, r;
    io >> n >> m >> r;
    rep (i, 1, n)
        io >> a[i]; // ***
    re (i, 1, n) {
        int u, v;
        io >> u >> v;
        // ccc(u, v);
        arc(&g[u], &g[v]);
    }
    dfs(&g[r], NULL);
    rep (i, 1, n)
        bit::add(g[i].dl, a[i]);
    rep (i, 1, m) {
        int op, u;
        io >> op >> u;
        // ccc(i, op, u);
        if (op == 1) bit::add(g[u].dl, io);
        else io << bit::query(g[u].dl, g[u].dr) daze;
    }
}
