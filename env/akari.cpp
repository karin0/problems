#pragma GCC optimize "Ofast,no-stack-protector"
#include <bits/stdc++.h>

#ifdef AKARI
void cca() {
    std::cerr << "\033[39;0m" << std::endl;
}
template <typename T, typename... Args>
void cca(T a, Args... args) {
    std::cerr << a << ", ";
    cca(args...);
}
    #define ccc(args...) std::cerr << "\033[32;1m" << #args << "  =  ", cca(args)
    #define ccd(args...) std::cerr << "\033[32;1m", cca(args)
    #define ccf(args...) fprintf(stderr, args)
    #define crep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#else
    #define ccc(...) 0
    #define ccd(...) 0
    #define ccf(...) 0
    #define crep(...) if (0)
#endif

#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)
#define pe(i_, s_, t_) for (int i_ = (s_); i_ > (t_); --i_)
#define go(e_, s_) for (Edge *e_ = (s_); e_; e_ = e_->e)
#define daze << '\n'

typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef const int cint;
typedef const long long cll;
typedef const char cchar;
typedef const unsigned int cuint;
typedef const unsigned long long cull;

template <int I, int O>
struct IO {
    char r[20];
#ifdef AKARI
    char gc() {
        return getchar();
    }
    void pc(cchar c) {
        putchar(c);
    }
#else
    char a[I], b[O], *s, *t, *z;
    std::streambuf *i, *o;
    IO() : z(b) {
        std::ios::sync_with_stdio(false);
        if (I) std::cin.tie(NULL), i = std::cin.rdbuf();
        if (O) std::cout.tie(NULL), o = std::cout.rdbuf();
    }
    ~IO() {
        if (O) o->sputn(b, z - b);
    }
    char gc() {
        if (s == t) t = (s = a) + i->sgetn(a, I);
        return *s++;
    }
    void pc(cchar c) {
        if (z == b + O) o->sputn(z = b, O);
        *z++ = c;
    }
#endif
    void gs(char *p) {
        char c;
        do c = gc(); while (!isgraph(c));
        do *p++ = c, c = gc(); while (isgraph(c));
        *p = 0;
    }
    IO &operator >> (char *p) {
        return gs(p), *this;
    }
    IO &operator >> (char &c) {
        do c = gc(); while (!isgraph(c));
        return *this;
    }
    template <class T>
    IO &operator >> (T &x) {
        char c;
        do c = gc(); while (!isdigit(c) && c != '-');
        bool f = c == '-';
        for (x = (f ? gc() : c) - '0'; isdigit(c = gc()); x = x * 10 + (c - '0'));
        if (f) x = -x;
        return *this;
    }
    template <class T>
    IO &operator > (T &x) {
        char c;
        do c = gc(); while (!isdigit(c) && c != '-');
        for (x = c - '0'; isdigit(c = gc()); x = x * 10 + (c - '0'));
        return *this;
    }
    template <class T>
    operator T () {
        T x;
        *this >> x;
        return x;
    }
    IO &operator << (char *p) {
        while (*p) pc(*p++);
        return *this;
    }
    IO &operator << (cchar *p) {
        while (*p) pc(*p++);
        return *this;
    }
    IO &operator << (cchar c) {
        return pc(c), *this;
    }
    template <class T>
    IO &operator << (T x) {
        if (x == 0) return pc('0'), *this;
        if (x < 0) pc('-'), x = -x;
        char *j = r;
        for (T y; x; x = y) y = x / 10, *j++ = x - y * 10 + '0';
        do pc(*--j); while (j != r);
        return *this;
    }
    template <class T>
    IO &operator < (T x) {
        if (x == 0) return pc('0'), *this;
        char *j = r;
        for (T y; x; x = y) y = x / 10, *j++ = x - y * 10 + '0';
        do pc(*--j); while (j != r);
        return *this;
    }
    template <class T>
    IO &operator - (T x) {
        char *j = r;
        for (T y; x; x = y) y = x / 10, *j++ = x - y * 10 + '0';
        do pc(*--j); while (j != r);
        return *this;
    }
};
