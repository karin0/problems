#include <bits/stdc++.h>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))
#ifdef AKARI
    #define SAY(x) std::cerr << #x " = " << x << std::endl
#else
    #define SAY(x) 0
#endif

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
    void print(T x, const char end = '\n') {
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
        if (end)
            pc(end);
    }
    void ps(const char *st, const char end = '\n') {
        while (*st)
            pc(*st++);
        if (end)
            pc(end);
    }
    inline void flush() const {
        fwrite(b, 1, p - b, stdout); // p = b;
    }
} io;

typedef long long ll;
const int Q = 40558;
int pcnt, pri[Q], mu[Q];
bool np[Q];
void sieve() {
    static int i, j;
    static ll t;
    static const int n = 40557;
    mu[1] = 1;
    rep (i, 2, n) {
        if (!np[i]) {
            pri[pcnt++] = i;
            mu[i] = -1;
        }
        for (j = 0; j < pcnt && (t = (ll)i * pri[j]) <= n; ++j) {
            np[t] = true;
            if (i % pri[j] == 0) {
                mu[t] = 0;
                break;
            }
            mu[t] = -mu[i];
        }
    }
}
int calc(const int n) {
    static int i, t, res;
    for (res = 0, i = 1; (t = i * i) <= n; ++i)
        res += mu[i] * (n / t);
    return res;
}
int solve(const int n) {  // Find min x such that calc(x) = n
    static int l, r, x;
    l = 0, r = 1644934081;
    while (r - l > 1) {
        x = l + ((r - l) >> 1);
        (calc(x) < n ? l : r) = x;
    }
    return r;
}
int main() {
    static int ks;
    ks = io;
    sieve();
    while (ks--)
        io.print(solve(io));

    io.flush();
    return 0;
}
