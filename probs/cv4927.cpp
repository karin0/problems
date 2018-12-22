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

cint N = 100003;

int n;
ll ret;
inline ll fsum(cll x, cll y) {
    return x + y;
}
struct Node {
    Node *lc, *rc;
    int len;
    ll sum, min, max, tgs, tga; // tgs goes first
    Node() {}
    Node(cll x) : lc(NULL), rc(NULL), len(1), sum(x), min(x), max(x), tgs(LLONG_MIN), tga(0) {}
    Node(Node *l, Node *r, cint le) : lc(l), rc(r), len(le), tgs(LLONG_MIN), tga(0) {
        maintain();
    }
    void maintain() {
        sum = lc->sum + rc->sum;
        min = std::min(lc->min, rc->min);
        max = std::max(lc->max, rc->max);
    }
    void cover_s(cll x) {
        sum = x * len;
        min = max = tgs = x;
        tga = 0;
    }
    void cover_a(cll x) {
        sum += x * len;
        min += x;
        max += x;
        tga += x;
    }
    void push_down() {
        if (tgs != LLONG_MIN) {
            lc->cover_s(tgs);
            rc->cover_s(tgs);
            tgs = LLONG_MIN;
        }
        if (tga) {
            lc->cover_a(tga);
            rc->cover_a(tga);
            tga = 0;
        }
    }
#define MODIFY_FUNC(func, coverrer) \
    void func(cint ql, cint qr, cll x, cint l = 1, cint r = n) { \
        if (qr < l || r < ql) \
            return; \
        if (ql <= l && r <= qr) \
            return coverrer(x); \
        push_down(); \
        int mid = (l + r) >> 1; \
        if (ql <= mid) \
            lc->func(ql, qr, x, l, mid); \
        if (qr > mid) \
            rc->func(ql, qr, x, mid + 1, r); \
        maintain(); \
    }
#define QUERY_FUNC(func, attr, opt) \
    void func(cint ql, cint qr, cint l = 1, cint r = n) { \
        if (qr < l || r < ql) \
            return; \
        if (ql <= l && r <= qr) { \
            ret = opt(ret, attr); \
            return; \
        } \
        push_down(); \
        int mid = (l + r) >> 1; \
        if (ql <= mid) \
            lc->func(ql, qr, l, mid); \
        if (qr > mid) \
            rc->func(ql, qr, mid + 1, r); \
    }
    MODIFY_FUNC(add, cover_a);
    MODIFY_FUNC(set, cover_s);
    QUERY_FUNC(qmin, min, std::min);
    QUERY_FUNC(qmax, max, std::max);
    QUERY_FUNC(qsum, sum, fsum);
} *segt;
Node *build(cint l, cint r) {
    static Node pool[N << 1], *curr = pool;
    if (l == r)
        return new (curr++) Node((ll)io);
    int mid = (l + r) >> 1;
    Node *lc = build(l, mid);
    return new (curr++) Node(lc, build(mid + 1, r), r - l + 1);
}

int main() {
    int m;
    io >> n >> m;
    segt = build(1, n);
    char opt[6];
    while (m--) {
        int l, r;
        io >> opt >> l >> r;
        if (opt[0] == 's') {
            if (opt[1] == 'u')
                ret = 0, segt->qsum(l, r), io << ret daze;
            else
                segt->set(l, r, io);
        } else if (opt[0] == 'm') {
            if (opt[1] == 'i')
                ret = LLONG_MAX, segt->qmin(l, r);
            else
                ret = LLONG_MIN, segt->qmax(l, r);
            io << ret daze;
        } else
            segt->add(l, r, io);
    }
}
