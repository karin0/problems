#include <cstdio>
#include <cctype>
#include <algorithm>
#include <map>
#include <cstdlib>
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
ll mul(ll a, ll b, ll mod) {
    static ll t;
    ll res = 0;
    a %= mod;
    for (; b; b >>= 1, a = (t = a + a) >= mod ? t - mod : t) if (b & 1) res = (t = res + a) >= mod ? t - mod : t;
    return res;
}
ll pow(ll a, ll n, ll mod) {
    ll res = 1;
    for (; n; n >>= 1, a = mul(a, a, mod)) if (n & 1) res = mul(res, a, mod);
    return res;
}
ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

bool _isPrime(ll n) {
    const static int primes[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    ll s = 0, d = n - 1;
    while ((d & 1) == 0) d >>= 1, s++;
    if (s == 0) return n == 2;
    for (int i = 0; i < 12 && primes[i] < n; i++) {
        ll a = primes[i];
        if (pow(a, d, n) != 1) {
            bool flag = true;
            for (int r = 0; r < s; r++) {
                if (flag && pow(a, d * (1 << r), n) == n - 1) {
                    flag = false;
                    break;
                }
            }
            if (flag) return false;
        }
    }
    return true;
}
std::map<ll, bool> isp;
bool isPrime(ll n) {
    static std::map<ll, bool>::iterator it;
    it = isp.find(n);
    if (it == isp.end())
        return isp[n] = _isPrime(n);
    return it->second;
}

ll p, q, b;
bool flag;
namespace PollardRho {
    ll g(ll x, ll n, ll c) {
        return (mul(x, x, n) + c) % n;
    }
    ll rho(ll n, ll c) {
        ll x = rand() % n, y = x, d = 1;
        for (ll i = 1, k = 2; d == 1; i++) {
            x = g(x, n, c);
            d = gcd(x > y ? x - y : y - x, n);
            if (x == y) return n;
            if (i == k) k <<= 1, y = x;
        }
        return d;
    }
    void find(ll n, ll c) {
        if (flag || n == 1) return;
        if (isPrime(n)) {
            if (b % n != 0)
                flag = true;
            return;
        }
        ll p = n;
        while (p == n) p = rho(p, c++);
        find(p, c);
        if (flag)
            return;
        find(n / p, c);
    }
}
int main() {
    srand(92618017);
    static int ks;
    ks = io;
    while (ks--) {
        p = io;
        q = io;
        b = io;
        q /= gcd(p, q);
        flag = false;
        if (b % q == 0)
            io.ps("Finite");
        else {
            PollardRho::find(q, 1);
            if (flag)
                io.ps("Infinite");
            else
                io.ps("Finite");
        }
    }

    io.flush();
    return 0;
}
