#include <cstdio>
#include <cctype>
#include <algorithm>
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
const int N = 10000003;
bool np[N];
int pcnt, pri[N], g[N], z[N], pz[N];
void sieve() {
    static int i, j, p, t;
    static ll ip;
    static const int n = 10000000;
    rep (i, 2, n) {
        if (!np[i]) {
            g[i] = z[i] = 1;
            pz[i] = i;
            pri[pcnt++] = i;
        }
        for (j = 0; j < pcnt && (ip = (ll)i * (p = pri[j])) <= n; ++j) {
            np[ip] = true;
            if (i % p) {
                g[ip] = z[i] == 1 ? -g[i] : 0;
                z[ip] = 1;
                pz[ip] = p;
            } else {
                if (pz[i] == i)
                    g[ip] = 1;
                else
                    g[ip] = (z[i] + 1 == z[i / pz[i]]) ? -g[i / pz[i]] : 0;
                z[ip] = z[i] + 1;
                pz[ip] = pz[i] * p;
                break;
            }
        }
    }
    rep (i, 2, n)
        g[i] += g[i - 1];
}
ll calc(int n, int m) {
    static int i, r, x, y;
    static ll ans;
    if (n > m)
        std::swap(n, m);
    ans = 0;
    for (i = 1; i <= n; i = r + 1) {
        x = n / i;
        y = m / i;
        r = std::min(n / x, m / y);
        ans += (ll)x * y * (g[r] - g[i - 1]);
    }
    return ans;
}
int main() {
    static int ks, n;
    ks = io;
    sieve();
    while (ks--) {
        n = io; 
        io.print(calc(n, (int)io));
    }

    io.flush();
    return 0;
}
