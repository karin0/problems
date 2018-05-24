#include <bits/stdc++.h>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))
#ifdef AKARI
    #define ccc(x) std::cerr << #x " = " << x << "  "
    #define cccc(x) std::cerr << #x " = " << x << std::endl
    #define ccccc(x) std::cerr << x << std::endl
#else
    #define ccc(x) 0
    #define cccc(x) 0
    #define ccccc(x) 0
#endif
typedef long long ll;

struct IO {
    static const int L = 1000000;
    char a[L], b[L], *s, *t, *p;
    IO() : p(b) {}
    ~IO() {
        fwrite(b, 1, p - b, stdout); // p = b;
    }
    char gc() {
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
    void pc(const char c) {
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
} io;

const int U = 10000011, mo = 1000000007, inv6 = 166666668;
const ll mo2 = 1ll * mo * mo, inv6_2 = 833333345000000041ll;    // must solve it with extgcd
int pri[U], pcnt, mu[U];
bool np[U];
ll m, ms;
void sieve(const int n) {
    static int i, j;
    static ll v;
    mu[1] = 1;
    rep (i, 2, n) {
        if (!np[i]) {
            pri[++pcnt] = i;
            mu[i] = -1;
        }
        for (j = 1; j <= pcnt && (v = (ll)i * pri[j]) <= n; ++j) {
            np[v] = true;   // *****
            if (i % pri[j] == 0) {
                mu[v] = 0;
                break;
            }
            mu[v] = -mu[i];
        }
    }
    rep (i, 2, n)
        mu[i] += mu[i - 1];
}
namespace ns1 {
    ll mck(ll x) {
        return x >= mo ? x - mo : x;
    }
    ll mck2(ll x) {
        return x < 0 ? x + mo : mck(x);
    }
    ll qpow(ll a, ll n) {
        static ll res;
        for (res = 1; n; n >>= 1, a = a * a % mo)
            if (n & 1)
                res = res * a % mo;
        return res;
    }
    ll inv(ll x) {
        return qpow(x, mo - 2);
    }
    ll f(const ll n) {
        return mck2(ms * ((n & 1) ? -1 : 1) + qpow(ms, n));
    }
}
namespace ns2 {
    ll mck(ll x) {
        return x >= mo2 ? x - mo2 : x;
    }
    ll mck2(ll x) {
        return x < 0 ? x + mo2 : mck(x);
    }
    /* ll qmul(ll a, ll b) {
        static ll res;
        for (res = 0; b; b >>= 1, a = mck(a + a))
            if (b & 1)
                res = mck(res + a);
        return res;
    } */
    ll qmul(ll a, ll b) {
        return (a * b - (ll)((long double)a / mo2 * b + 1e-5) * mo2 + mo2) % mo2;
    }
    ll qpow(ll a, ll n) {
        static ll res;
        for (res = 1; n; n >>= 1, a = qmul(a, a))
            if (n & 1)
                res = qmul(res, a);
        return res;
    }
    // ns1 should not provide inv()
    ll f(const ll n) {
        return mck2(mck2(m - 1) * ((n & 1) ? -1 : 1) + qpow(mck2(m - 1), n));
    }
}
ll cres, n, pf[U * 2];
int a, pc[U * 2], pfc;
namespace ns1 {
    void calc(int i, ll x, ll phi) {
        if (i > pfc) {
            cres = mck(cres + f(n / x) * (phi % mo) % mo);
            return;
        }
        calc(i + 1, x, phi);
        ll p = pf[i];  // ******************************************************************************
        int c = pc[i], j;
        x *= p;
        phi *= p - 1;
        for (j = 1; j <= c; ++j, x *= p, phi *= p)
            calc(i + 1, x, phi);
    }
    ll solve() {
        static int i, r;
        static ll nn, c2, x, t;
        m = 0;
        c2 = 0;
        for (i = 1; i <= a; i = r + 1) {
            x = a / i;
            r = a / x;
            t = x * x % mo * mck2(mu[r] - mu[i - 1]) % mo;  // ******
            c2 = mck(c2 + t);
            m = mck(m + t * x % mo);
        }
        m = (ll)mck(m + (c2 * 3 + 2) % mo) * inv6 % mo;
        if (n == 1)
            return m;
        ms = mck2(m - 1);
        nn = n;
        pfc = 0;
        /*
        for (i = 1; i <= pcnt && nn > 1; ++i) {
            if (nn % (r = pri[i]) == 0) {
                pf[++pfc] = r;
                pc[pfc] = 1;
                nn /= r;
                while (nn % r == 0) {
                    nn /= r;
                    ++pc[pfc];
                }
            }
        }
        if (nn > 1) {
            pf[++pfc] = nn;
            pc[pfc] = 1;
        }*/
        for (i = 1; i <= pcnt && nn > 1; ++i) {
            if (nn % (r = pri[i]) == 0) {
                pf[++pfc] = r;
                pc[pfc] = 1;
                nn /= r;
                while (nn % r == 0) {
                    nn /= r;
                    ++pc[pfc];
                }
            }
        }
        if (nn > 1) {
            pf[++pfc] = nn;
            pc[pfc] = 1;
        }
        cres = 0;
        calc(1, 1, 1);
        return cres * inv(n % mo) % mo;
    }
}
namespace ns2 {
    void calc(int i, ll x, ll phi) {
        if (i > pfc) {
            cres = mck(cres + qmul(f(n / x), phi % mo2));
            return;
        }
        calc(i + 1, x, phi);
        ll p = pf[i];   // ******************************************************************************
        int c = pc[i], j;
        x *= p;
        phi *= p - 1;
        for (j = 1; j <= c; ++j, x *= p, phi *= p)
            calc(i + 1, x, phi);
    }
    /* void exgcd(ll a, ll b, ll &x, ll &y) {
        if (b)
            exgcd(b, a % b, y, x), y -= x * (a / b);
        else
            x = 1, y = 0;
    } */
    ll solve() {
        static ll i, r, nn, c2, x, y;
        m = 0;
        c2 = 0;
        for (i = 1; i <= a; i = r + 1) {
            x = a / i;
            r = a / x;
            y = qmul(x * x, mck2(mu[r] - mu[i - 1]));
            c2 = mck(c2 + y);
            m = mck(m + qmul(y, x));
        }
        m = qmul(mck(m + (c2 * 3 + 2) % mo2), inv6_2);
        if (n == 1)
            return m;
        ms = mck2(m - 1);
        nn = n;
        pfc = 0;
        /*
        for (i = 2; i * i <= nn; ++i) {
            if (nn % i == 0) {
                pf[++pfc] = i;
                pc[pfc] = 1;
                nn /= i;
                while (nn % i == 0) {
                    nn /= i;
                    ++pc[pfc];
                }
            }
        }
        if (nn > 1) {
            pf[++pfc] = nn;
            pc[pfc] = 1;
        }*/
        for (i = 1; i <= pcnt && nn > 1; ++i) {
            if (nn % (r = pri[i]) == 0) {
                pf[++pfc] = r;
                pc[pfc] = 1;
                nn /= r;
                while (nn % r == 0) {
                    nn /= r;
                    ++pc[pfc];
                }
            }
        }
        if (nn > 1) {
            pf[++pfc] = nn;
            pc[pfc] = 1;
        }
        cres = 0;
        calc(1, 1, 1);
        
        /*
        exgcd(n / mo, mo2, x, y);
        x %= mo2;
        if (x < 0)
            x += mo2;
        x %= mo;
        // return cres / mo % mo * x % mo;*/
        return cres / mo * ns1::inv(n / mo) % mo;
    }
}
int main() {
    static int ks;
    sieve(10000009);
    ks = io;
    while (ks--) {
        n = io;
        a = io;
        io.print(n % mo ? ns1::solve() : ns2::solve());
    }

    return 0;
}
