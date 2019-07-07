#include <bits/stdc++.h>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)
#define pe(i_, s_, t_) for (int i_ = (s_); i_ > (t_); --i_)
#ifdef AKARI
    void c_() { std::cerr << "\033[39;0m" << std::endl; }
    template <typename T, typename... Args>
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

// #define FI "tree"

template <cint LI, cint LO>
struct IO {
    char a[LI], b[LO], r[std::max(LO, 20)], *s, *t, *z, c;
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
        x = (f ? gc() : c) - '0';
        for (c = gc(); isdigit(c); c = gc())
            x = x * 10 + (c - '0');
        if (f) x = -x;
        return *this;
    }
    char *gs(char *x) {
        for (c = gc(); !isgraph(c); c = gc());
        for (*x++ = c, c = gc(); isgraph(c); *x++ = c, c = gc());
        return *x = 0, x;
    }
    IO &operator >> (char *x) {
        for (c = gc(); !isgraph(c); c = gc());
        for (*x++ = c, c = gc(); isgraph(c); *x++ = c, c = gc());
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
        char *j = r;
        for (T y; x; x = y) y = x / 10, *j++ = x - y * 10 + '0';
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

cint N = 1000002;

void get(int &x) {
    io >> x;
    if (x == -1)
        x = 0;
}
int a[N], lc[N], rc[N];

cint low = -10000000;
int go(cint u, cint v) {
    if (!u)
        return v ? low : 0;
    if (!v || a[u] != a[v])
        return low;
    int r1 = go(lc[u], rc[v]);
    if (r1 < 0) return low;
    int r2 = go(rc[u], lc[v]);
    if (r2 < 0) return low;
    return r1 + r2 + 2;
}
inline int go(cint u) {
    return go(lc[u], rc[u]) + 1;
}

int main() {
#ifdef FI
    freopen(FI ".in", "r", stdin);
    freopen(FI ".out", "w", stdout);
#endif
    int n = io, ans = 1;
    rep (i, 1, n)
        io >> a[i];
    rep (i, 1, n)
        get(lc[i]), get(rc[i]);
    rep (i, 1, n)
        ans = std::max(ans, go(i));
    io << ans daze;
    return 0;
}
