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
        return *s++; // return s == t ? -1 : *s++;
    }
    void gs(char *st) {
        static char c;
        for (c = gc(); !isgraph(c); c = gc());
        *st++ = c;
        for (c = gc(); isgraph(c); c = gc())
            *st++ = c;
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
        if (neg)
            x = -x;
        return x;
    }
    inline void pc(const char c) {
        if (p == b + L)
            fwrite(b, 1, L, stdout), p = b;
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
const int K = 1100000, mo = 1000000007, inv2 = 500000004, inv6 = 166666668;
bool np[K + 2];
int pri[K + 2], pcnt, k;
ll phi[K + 2];
void sieve(const int n) {
    static int i, j;
    static ll v;
    np[0] = np[1] = true;
    phi[1] = 1;
    rep (i, 2, n) {
        if (!np[i]) {
            pri[pcnt++] = i;
            phi[i] = i - 1;
        }
        for (j = 0; j < pcnt && (v = (ll)i * pri[j]) <= n; ++j) {
            np[v] = true;
            if (i % pri[j] == 0) {
                phi[v] = phi[i] * pri[j] % mo;
                break;
            }
            phi[v] = phi[i] * (pri[j] - 1) % mo;
        }
    }
    rep (i, 2, n)
        (phi[i] *= i) %= mo;
    rep (i, 2, n)
        (phi[i] += phi[i - 1]) %= mo;
}

/* int pow(ll a, ll n) {
    static ll res;
    for (res = 1; n; a = a * a % mo, n >>= 1)
        if (n & 1)
            res = res * a % mo;
    return res;

} */
std::map<int, int> s;
ll calc(int n) {
    if (n <= k)
        return phi[n];
    std::map<int, int>::iterator it;
    if ((it = s.find(n)) != s.end())
        return it->second;
    ll rphi, res;
    int i, ni, r;
    res = (ll)n * (n + 1) % mo * (2 * n + 1) % mo * inv6 % mo;
    for (i = 2; i <= n; i = ni + 1) {
        r = n / i;
        ni = n / r;
        res = (res + mo - (ll)calc(r) * (i + ni) % mo * (ni - i + 1) % mo * inv2 % mo) % mo;
    }
    s[n] = res;
    return res;
}

int main() {
    static int n;
    n = io;
    sieve(k = ceil(pow(n, 2.0 / 3.0)));
    io.ps("1");
    io.print(calc(n));
    io.flush(); // ***
    return 0;
}
