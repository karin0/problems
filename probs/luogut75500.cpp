#include <bits/stdc++.h>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)
#define pe(i_, s_, t_) for (int i_ = (s_); i_ > (t_); --i_)
#define go(e_, s_) for (Edge *e_ = (s_); e_; e_ = e_->e)
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

template <cint LI, cint LO>
struct IO {
    char a[LI], b[LO], r[20], *s, *t, *z, c;
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
IO<1000000, 25> io;

cint N = 100003;

struct Item {
    ll x;
    int p;
    bool operator < (const Item &rhs) {
        return x < rhs.x || (x == rhs.x && p < rhs.p);
    }
} a[N];
struct Range {
    int l, r;
    Range() {}
    Range(cint a) : l(a), r(a) {}
    Range(cint a, cint b) : l(a), r(b) {}
    Range operator & (const Range &rhs) {
        return Range(std::min(l, rhs.l), std::max(r, rhs.r));
    }
} st[17][N];
int n, lg[N];
inline void build() {
    lg[0] = -2;
    rep (i, 0, n) {
        st[0][i] = Range(a[i].p);
        lg[i] = lg[i >> 1] + 1;
    }
    for (int j = 1; (1 << j) <= n + 1; ++j)
        for (int i = 0; i + (1 << j) - 1 <= n; ++i)
            st[j][i] = st[j - 1][i] & st[j - 1][i + (1 << (j - 1))];
}
inline Range query(cint l, cint r) {
    cint k = lg[r - l + 1];
    return st[k][l] & st[k][r - (1 << k) + 1];
}
int main() {
    ll lim, s = 0;
    io >> n >> lim;
    rep (i, 1, n) {
        a[i].x = (s += (int)io);
        a[i].p = i;
    }
    std::sort(a, a + n + 1);
    int ans = 0, pos;
    build();
    for (int l = 0, r = 0; r <= n; ++r) {
        ll t = a[r].x - lim;
        while (l < r && a[l].x < t)
            ++l;
        if (a[l].x >= t) {
            Range ret = query(l, r);
            int len = ret.r - ret.l;
            if (len > ans)
                ans = len, pos = ret.l; 
        }
    }
    if (ans)
        io << ans << '\n' << pos << ' ' << n - pos - ans << '\n';
    else
        io << "-1\n";
}
