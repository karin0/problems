#include <bits/stdc++.h>
#ifdef AKARI
    #include <akaza_akari>
#else
    #define ccc(...) 0
    #define ccd(...) 0
    #define ccf(...) 0
    #define crep(...) if (false)
#endif
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)
#define pe(i_, s_, t_) for (int i_ = (s_); i_ > (t_); --i_)
#define go(e_, s_) for (Edge *e_ = (s_); e_; e_ = e_->e)
typedef long long ll;
typedef const int cint;
typedef const long long cll;
typedef const char cchar;
#define daze << '\n'

template <cint I, cint O>
struct IO {
#ifdef AKARI
    char gc() { return getchar(); }
    void pc(cchar c) { putchar(c); }
#else
    char a[I], b[O], *s, *t, *z;
    std::streambuf *i, *o;
    IO() : z(b) {
        std::ios::sync_with_stdio(false);
        if (I) std::cin.tie(NULL), i = std::cin.rdbuf();
        if (O) std::cout.tie(NULL), o = std::cout.rdbuf();
    }
    ~IO() { if (O) o->sputn(b, z - b); }
    char gc() {
        if (s == t) t = (s = a) + i->sgetn(a, I);
        return s == t ? EOF : *s++;
    }
    void pc(cchar x) {
        if (z == b + O) o->sputn(z = b, O);
        *z++ = x;
    }
#endif
    template <class T>
    IO &operator >> (T &x) {
        char c;
        for (c = gc(); c != '-' && !isdigit(c); c = gc());
        bool f = c == '-';
        x = (f ? gc() : c) - '0';
        for (c = gc(); isdigit(c); c = gc())
            x = x * 10 + (c - '0');
        if (f) x = -x;
        return *this;
    }
    char *gs(char *p) {
        char c;
        for (c = gc(); !isgraph(c); c = gc());
        for (*p++ = c, c = gc(); isgraph(c); *p++ = c, c = gc());
        return *p = 0, p;
    }
    IO &operator >> (char *p) {
        char c;
        for (c = gc(); !isgraph(c); c = gc());
        for (*p++ = c, c = gc(); isgraph(c); *p++ = c, c = gc());
        return *p = 0, *this;
    }
    IO &operator >> (char &c) {
        for (c = gc(); !isgraph(c); c = gc());
        return *this;
    }
    template <class T>
    operator T () { T x; *this >> x; return x; }
    template <class T>
    IO &operator << (T x) {
        static char r[20];
        if (x == 0) return pc('0'), *this;
        if (x < 0) pc('-'), x = -x;
        char *j = r;
        for (T y; x; x = y) y = x / 10, *j++ = x - y * 10 + '0';
        while (j != r) pc(*--j);
        return *this;
    }
    IO &operator << (char *p) {
        while (*p) pc(*p++);
        return *this;
    }
    IO &operator << (cchar *p) {
        while (*p) pc(*p++);
        return *this;
    }
    IO &operator << (cchar x) { return pc(x), *this; }
};
IO<1000000, 1000000> io;

cint N = 100002;

int main() {
    return 0;
}
