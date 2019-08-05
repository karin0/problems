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

#define FI "bus"

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
IO<1000000, 10> io;

cint N = 502, M2 = 102 * 2, inf = 0x3f3f3f3f;

inline void upd(int &x, cint v) {
    if (v < x) x = v;
}
int a[N], f[N][M2];
int main() {
#ifdef FI
    freopen(FI ".in", "r", stdin);
    freopen(FI ".out", "w", stdout);
#endif
    int n, m;
    io >> n >> m;
    rep (i, 1, n)
        io >> a[i];
    std::sort(a + 1, a + n + 1);
    int m2 = m << 1;

	int *fi = f[1], *fii = f[2];
    rep (j, 0, m2)
        fi[j] = j;
	rep (i, 2, n) {
		rep (j, 0, m2)
			fii[j] = inf;
		fii += M2;
	}
	fii = f[2];
    // memset(f, 0x3f, sizeof(f));
    re (i, 1, n) {
		int c = a[i] - a[i + 1], cm = c + m;
        rep (j, 0, m2) {
            if (fi[j] >= inf)
                continue;
            int k;
            if ((k = c + j) >= 0) {
                if (k <= m2)
                    upd(fii[k], fi[j] + k);
            } else
                rep (k, std::max(0, cm + j), m2)
                    upd(fii[k], fi[j] + k);
        }
		fi += M2;
		fii += M2;
	}

    io << *std::min_element(f[n], f[n] + m2 + 1) daze;
    return 0;
}


