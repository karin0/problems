#include <bits/stdc++.h>
#define rep(i_,s_,t_) for(int i_=(s_);i_<=(t_);++i_)
#define re(i_,s_,t_) for(int i_=(s_);i_<(t_);++i_)
#define per(i_,s_,t_) for(int i_=(s_);i_>=(t_);--i_)
#define pe(i_,s_,t_) for(int i_=(s_);i_>(t_);--i_)
#define koishi(e_,u_) for(Edge *e_=(u)_->e;e_;e_=e_->e)
#ifdef AKARI
    void c_() { std::cerr << "\033[39;0m" << std::endl; }
    template<typename T, typename... Args>
    void c_(T a, Args... args) { std::cerr << a << ", "; c_(args...); }
    #define ccc(args...) std::cerr << "\033[32;1m" << #args << "  =  ", c_(args)
    #define ccd(args...) std::cerr << "\033[32;1m", c_(args)
    #define ccf(args...) fprintf(stderr, args)
    #define drep(i_,s_,t_) for(int (i_)=(s_);(i_)<=(t_);++(i_))
#else
    #define ccc(...) 0
    #define ccd(...) 0
    #define ccf(...) 0
    #define drep(i_,s_,t_) if (false)
#endif
typedef long long ll;
typedef const int cint;
typedef const long long cll;
typedef const char cchar;
#define daze << '\n'
struct IO {
    static cint L = 1000000;
    char a[L], b[L], r[30], *s, *t, *z;
    IO() : z(b) {}
    ~IO() { if (z != b) fwrite(b, 1, z - b, stdout); }
    char gc() {
        if (s == t) t = (s = a) + fread(a, 1, L, stdin);
        return s == t ? EOF : *s++;
    }
    template <class T>
    IO &operator >> (T &x) {
        char c = gc();
        for (; c != '-' && !isdigit(c); c = gc());
        bool f = c == '-';
        if (f) c = gc();
        x = c - '0';
        for (c = gc(); isdigit(c); c = gc())
            x = x * 10 + (c - '0');
        if (f) x = -x;
        return *this;
    }
    IO &operator >> (char *q) {
        char c = gc();
        for (; !isgraph(c); c = gc());
        *q++ = c;
        for (c = gc(); isgraph(c); *q++ = c, c = gc());
        *q++ = 0;
        return *this;
    }
    IO &operator >> (char &q) {
        for (q = gc(); !isgraph(q); q = gc());
        return *this;
    }
    template <class T>
    operator T () { T x; *this >> x; return x; }
    void pc(cchar x) {
        if (z == b + L) fwrite(z = b, 1, L, stdout);
        *z++ = x;
    }
    void fl() {
        fwrite(b, 1, z - b, stdout);
        z = b;
    }
    template <class T>
    struct d {
        T x;
        int l;
        d(const T x_, cint l_) : x(x_), l(l_) {}
    };
    template <class T> static d<T> dio(const T x, const int l) { return d<T>(x, l); }
    template <class T>
    IO &operator << (T x) {
        if (x == 0) pc('0');
        else {
            if (x < 0) pc('-'), x = -x;
            T y; char *j;
            for (j = r; x; x = y)
                y = x / 10, *j++ = x - y * 10 + '0';
            while (j != r) pc(*--j);
        }
        return *this;
    }
    template <class T>
    IO &operator << (d<T> x) {
        if (x.x == 0) while (x.l--) pc('0');
        else {
            if (x.x < 0) pc('-'), x.x = -x.x;
            T y; char *j;
            for (j = r; x.x; x.x = y, --x.l)
                y = x.x / 10, *j++ = x.x - y * 10 + '0';
            for (; x.l > 0; pc('0'), --x.l);
            while (j != r) pc(*--j);
        }
        return *this;
    }
    IO &operator << (d<double> x) {
        if (x.x < 0) pc('-'), x.x = -x.x;
        int w = floor(x.x);
        *this << w;
        pc('.');
        int e = (x.x - w) * pow(10, x.l + 1);
        if (e % 10 >= 5)
            e /= 10, ++e;
        else
            e /= 10;
        return *this << d<int>(e, x.l);
    }
    IO &operator << (cchar *x) {
        while (*x) pc(*x++);
        return *this;
    }
    IO &operator << (cchar x) {
        pc(x);
        return *this;
    }
} io;

const int N = 0;

int main() {

    return 0;
}

