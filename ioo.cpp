#include <bits/stdc++.h>
#define rep(i_,s_,t_) for((i_)=(s_);(i_)<=(t_);++(i_))
#define re(i_,s_,t_) for((i_)=(s_);(i_)<(t_);++(i_))
#define per(i_,s_,t_) for((i_)=(s_);(i_)>=(t_);--(i_))
#define pe(i_,s_,t_) for((i_)=(s_);(i_)>(t_);--(i_))
#define koishi(e_,u_) for(Edge *e_=(u)_->e;e_;e_=e_->e)
#ifdef AKARI
    void c_() { std::cerr << "\033[39;0m" << std::endl; }
    template<typename T, typename... Args>
    void c_(T a, Args... args) { std::cerr << a << ", "; c_(args...); }
    #define ccc(args...) std::cerr << "\033[32;1m" << #args << "  =  ", c_(args)
    #define ccd(args...) std::cerr << "\033[32;1m", c_(args)
    #define ccf(args...) fprintf(stderr, args)
#else
    #define ccc(...) 0
    #define ccd(...) 0
    #define ccf(...) 0
#endif
typedef long long ll;
typedef const int cint;
typedef const long long cll;
typedef const char cchar;
struct IO {
    static cint L = 1000000;
    char a[L], b[L], *s, *t, *z, c;
    IO() : z(b) {}
    ~IO() {
        fl();
    }
    char gc() {
        if (s == t)
            t = (s = a) + fread(a, 1, L, stdin);
        return s == t ? EOF : *s++;
    }
    template <class T>
    operator T() {
        static T x;
        static bool f;
        for (c = gc(); c != '-' && !isdigit(c); c = gc());
        if ((f = c == '-'))
            c = gc();
        x = c - '0';
        for (c = gc(); isdigit(c); c = gc())
            x = x * 10 + (c - '0');
        return f ? -x : x;
    }
    void gs(char *q) {
        for (c = gc(); !isgraph(c); c = gc());
        *q++ = c;
        for (c = gc(); isgraph(c); c = gc())
            *q++ = c;
        *q++ = 0;
    }
    char gg() {
        for (c = gc(); !isgraph(c); c = gc());
        return c;
    }
    void pc(cchar q) {
        if (z == b + L)
            fwrite(z = b, 1, L, stdout);
        *z++ = q;
    }
    void fl() {
        fwrite(b, 1, z - b, stdout);
        z = b;
    }
    template<class T>
    void operator () (T x, cchar e = '\n') {
        static char r[30], *q;
        static T y;
        if (x == 0)
            pc('0');
        else {
            if (x < 0)
                pc('-'), x = -x;
            for (q = r; x; x = y)
                y = x / 10, *q++ = x - y * 10 + '0';
            while (q != r)
                pc(*--q);
        }
        if (e)
            pc(e);
    }
    void ps(cchar *q, cchar e = '\n') {
        while (*q)
            pc(*q++);
        if (e)
            pc(e);
    }
    void pd(cint x) {
        pc('0' + x);
        pc('\n');
    }
} io;

const int N = 0;

int main() {
    static int i;

    return 0;
}

