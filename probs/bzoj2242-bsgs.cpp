#include <cstdio>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <map>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))

struct IO {
    static const int L = 1000000;
    char a[L], b[L], *s, *t, *p;
    IO() : p(b) {}
    inline char gc() {
        if (s == t)
            t = (s = a) + fread(a, 1, L, stdin);
        return *s++; // return s == t ? EOF : *s++;
    }
    void gs(char *st) {
        static char c;
        for (c = gc(); !isgraph(c); c = gc());
        *st++ = c;
        for (c = gc(); isgraph(c); c = gc())
            *st++ = c;
        *st++ = 0;
    }
    template <class T>
    operator T() {
        static T x;
        static char c;
        static bool neg;
        for (c = gc(); c != '-' && !isdigit(c); c = gc());
        if (c == '-')
            neg = true, c = gc();
        else
            neg = false;
        x = c - '0';
        for (c = gc(); isdigit(c); c = gc())
            x = x * 10 + (c - '0');
        return neg ? -x : x;
    }
    inline void pc(const char c) {
        if (p == b + L)
            fwrite(p = b, 1, L, stdout);
        *p++ = c;
    }
    template<class T>
    void print(T x, const bool nl = true) {
        static char c[30], *q;
        static T y;
        if (x == 0)
            pc('0');
        else {
            if (x < 0)
                pc('-'), x = -x;
            for (q = c; x; x = y)
                y = x / 10, *q++ = x - y * 10 + '0';
            while (q != c)
                pc(*--q);
        }
        if (nl)
            pc('\n');
    }
    void ps(const char *st, const bool nl = true) {
        while (*st)
            pc(*st++);
        if (nl)
            pc('\n');
    }
    inline void flush() const {
        fwrite(b, 1, p - b, stdout); // p = b;
    }
} io;

typedef long long ll;
int pow(ll a, int n, const int p) {
    static ll res;
    for (res = 1; n; n >>= 1, a = a * a % p)
        if (n & 1)
            res = res * a % p;
    return res;
}
inline int inv(const int a, const int p) {
    return pow(a, p - 2, p);
}
int bsgs(const int a, int n, const int p) {
    static int t, q, i;
    static ll v;
    if (a == 0)
        return n ? -1 : 1;
    t = ceil(sqrt(p));
    std::map<int, int> tb;
    v = 1;
    re (i, 0, t) {
        if (!tb.count(v))
            tb[v] = i;
        v = v * a % p;
    }
    q = inv(v, p), v = n;
    re (i, 0, t) {
        if (tb.count(v))
            return i * t + tb[v];
        v = v * q % p;
    }
    return -1;
}
inline void solve_1(const int x, const int y, const int p) {
    io.print(pow(x, y, p));
}
inline void solve_2(int x, int y, const int p) {
    y %= p;
    if (y == 0)
        io.print(0);
    else {
        x %= p;
        if (x == 0)
           io.ps("Orz, I cannot find x!");
        else
            io.print((int)(y * (ll)inv(x, p) % p));
    }
}
inline void solve_3(const int x, const int y, const int p) { // \log_x {y}
    static int res;
    res = bsgs(x % p, y % p, p);
    if (res < 0)
        io.ps("Orz, I cannot find x!");
    else
        io.print(res);
}

int main() {
    static int ks, typ, x, y;
    ks = io;
    typ = io;
    switch (typ) {
        case 1: while (ks--) {x = io; y = io; solve_1(x, y, io);} break;
        case 2: while (ks--) {x = io; y = io; solve_2(x, y, io);} break;
        default: while (ks--) {x = io; y = io; solve_3(x, y, io);}
    }

    io.flush();
    return 0;
}
