#pragma GCC optimize("Ofast", "unroll-loops", "no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
#include <bits/stdc++.h>

#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)
#define pe(i_, s_, t_) for (int i_ = (s_); i_ > (t_); --i_)
#define daze << '\n'

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
    #define ccf(args...) fprintf(stderr, args)
    #define crep(i_, s_, t_) rep(i, s_, t_)
#else
    #define ccc(...) 0
    #define ccf(...) 0
    #define crep(...) if (0)
#endif

typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef const int cint;
typedef const long long cll;
typedef const char cchar;
typedef const unsigned int cuint;
typedef const unsigned long long cull;

template <class T, class U> struct if_int;
template <class U> struct if_int<short, U> { typedef U type; };
template <class U> struct if_int<int, U> { typedef U type; };
template <class U> struct if_int<ll, U> { typedef U type; };
template <class U> struct if_int<unsigned short, U> { typedef U type; };
template <class U> struct if_int<uint, U> { typedef U type; };
template <class U> struct if_int<ull, U> { typedef U type; };

#ifndef I
    #define I 0
#endif
#ifndef O
    #define O 0
#endif

struct Buf {
    char r[20];
#if !defined(AKARI) && (I > 0 || O > 0)
    char a[I], b[O], *s, *t, *z;
    std::streambuf *i, *o;
    Buf() : z(b) {
        std::ios::sync_with_stdio(false);
#if I > 0
        std::cin.tie(NULL);
        i = std::cin.rdbuf();
#endif
#if O > 0
        std::cout.tie(NULL);
        o = std::cout.rdbuf();
#endif
    }
#if O > 0
    ~Buf() { o->sputn(b, z - b); }
#endif
    char operator () () {
        if (s == t) t = (s = a) + i->sgetn(a, I);
        return *s++;
    }
    void operator () (cchar c) {
        if (z == b + O) o->sputn(z = b, O);
        *z++ = c;
    }
#else
    char operator () () { return getchar(); }
    void operator () (cchar c) { putchar(c); }
#endif
} buf;

struct IO {
    char *gs(char *p) {
        char c;
        while (!isgraph(c = buf()));
        while (*p++ = c, isgraph(c = buf()));
        return *p = 0, p;
    }
    void get(char *p) {
        char c;
        while (!isgraph(c = buf()));
        while (*p++ = c, isgraph(c = buf()));
        *p = 0;
    }
    void get(char &c) {
        while (!isgraph(c = buf()));
    }
    template <class T>
    typename if_int<T, void>::type get(T &x) {
        char c;
        while (!isdigit(c = buf()) && c != '-');
        if (c == '-')
            for (x = '0' - buf(); isdigit(c = buf()); x = x * 10 + ('0' - c));
        else
            for (x = c - '0'; isdigit(c = buf()); x = x * 10 + (c - '0'));
    }
    void put(char *p) {
        while (*p) buf(*p++);
    }
    void put(cchar *p) {
        while (*p) buf(*p++);
    }
    void put(cchar c) { buf(c); }
    template <class T>
    typename if_int<T, void>::type put(T x) {
        if (x < 0) buf('-'), x = -x;
        else if (x == 0) return buf('0');
        char *j = buf.r;
        for (T y; x; y = x / 10, *j++ = x - y * 10 + '0', x = y);
        while (buf(*--j), j != buf.r);
    }
    template <class T>
    operator T () {
        T x;
        return get(x), x;
    }
    IO &operator >> (char *x) { return get(x), *this; }
    template <class T>
    IO &operator >> (T &x) { return get(x), *this; }
    template <class T>
    IO &operator << (T x) { return put(x), *this; }
} io;

struct UIO : IO {
    using IO::get;
    using IO::put;
    template <class T>
    typename if_int<T, void>::type get(T &x) {
        char c;
        while (!isdigit(c = buf()) && c != '-');
        for (x = c - '0'; isdigit(c = buf()); x = x * 10 + (c - '0'));
    }
    template <class T>
    typename if_int<T, void>::type put(T x) {
        if (x == 0) return buf('0');
        char *j = buf.r;
        for (T y; x; y = x / 10, *j++ = x - y * 10 + '0', x = y);
        while (buf(*--j), j != buf.r);
    }
    template <class T>
    operator T () {
        T x;
        return get(x), x;
    }
    UIO &operator >> (char *x) { return get(x), *this; }
    template <class T>
    UIO &operator >> (T &x) { return get(x), *this; }
    template <class T>
    UIO &operator << (T x) { return put(x), *this; }
} uio;

struct PIO : UIO {
    using UIO::get;
    using UIO::put;
    template <class T>
    typename if_int<T, void>::type put(T x) {
        char *j = buf.r;
        for (T y; x; y = x / 10, *j++ = x - y * 10 + '0', x = y);
        while (buf(*--j), j != buf.r);
    }
    PIO &operator >> (char *x) { return get(x), *this; }
    template <class T>
    PIO &operator >> (T &x) { return get(x), *this; }
    template <class T>
    PIO &operator << (T x) { return put(x), *this; }
} pio;
