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
int p, t, q;
int qpow(ll a, int n) {
    static ll res;
    for (res = 1; n; n >>= 1, a = a * a % p)
        if (n & 1)
            res = res * a % p;
    return res;
}
int lqpow(ll a, ll n) {
    static ll res;
    for (res = 1; n; n >>= 1, a = a * a % p)
        if (n & 1)
            res = res * a % p;
    return res;
}
int a; 
ll bsgs(const int n) { // ****      ll!!
    static int i;
    static ll v;
    static std::map<int, int>::iterator it;
    std::map<int, int> tb;
    v = 1;
    re (i, 0, t) {
        if (!tb.count(v))
            tb[v] = i;
        v = v * a % p;
    }
    v = n;
    re (i, 0, t) {
        it = tb.find(v);
        if (it != tb.end())
            return it->second + i * t;
        v = v * q % p;
    }
    return -1;
}

int main() {
    static int ks;
    a = io;
    p = io;
    ks = io;
    q = qpow(qpow(a, p - 2), t = ceil(sqrt(p)));
    while (ks--)
        io.print(lqpow(a, bsgs(io) * bsgs(io))); // ***** no mod

    io.flush();
    return 0;
}
