#include <bits/stdc++.h>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))
#ifdef AKARI
    #define ccc(x) std::cerr << #x " = " << x << "  "
    #define ccf(x) std::cerr << #x " = " << x << std::endl
    #define cccc(...) fprintf(stderr, __VA_ARGS__)
#else
    #define ccc(x) 0
    #define ccf(x) 0
    #define cccc(...) 0
#endif
typedef long long ll;
 
const int N = 1 << 18, mo = 1004535809, pr = 3;
int qpow(ll x, int n) {
    static ll res;
    for (res = 1; n; n >>= 1, x = x * x % mo)
        if (n & 1)
            res = res * x % mo;
    return res;
}
int mck(const int x) {
    return x >= mo ? x - mo : x;
}
int mck2(const int x) {
    return x < 0 ? x + mo : x;
}
namespace ntt {
    ll w[N], wi[N], ni;
    int n, rev[N];
    void init(const int _n) {
        static int i, x, xi, k;
        n = _n;
        for (k = 0, x = 1; x < n; x <<= 1, ++k);
        ni = qpow(n, mo - 2);
        x = qpow(pr, (mo - 1) / n);
        xi = qpow(x, mo - 2);
        w[0] = wi[0] = 1;
        re (i, 1, n) {
            w[i] = w[i - 1] * x % mo;
            wi[i] = wi[i - 1] * xi % mo;
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
        }
    }
    void dft(int *a, ll *w = ntt::w) {
        static int i, l, m, t, x, *p;
        re (i, 0, n)
            if (i < rev[i])
                std::swap(a[i], a[rev[i]]);
        for (l = 2; l <= n; l <<= 1) {
            m = l >> 1;
            t = n / l;
            for (p = a; p != a + n; p += l)
                re (i, 0, m) {
                    x = w[t * i] * p[m + i] % mo;
                    p[m + i] = mck2(p[i] - x);
                    p[i] = mck(p[i] + x);
                }
        }
    }
    void idft(int *a) {
        static int i;
        dft(a, wi);
        re (i, 0, n)
            a[i] = a[i] * ni % mo;
    }
}
void pinv(const int *a, const int n, int *b) {
    static int t[N];
    if (n == 1) {
        b[0] = qpow(a[0], mo - 2);
        return;
    }
    pinv(a, n >> 1, b);
    int l = n << 1, i;
    std::copy(a, a + n, t);
    std::fill(t + n, t + l, 0);
    ntt::init(l);
    ntt::dft(t);
    ntt::dft(b);
    re (i, 0, l)
        b[i] = (ll)b[i] * mck2(2 - (ll)t[i] * b[i] % mo) % mo;
    ntt::idft(b);
    std::fill(b + n, b + l, 0);
}
void pmul(int *a, int *b, const int n) { // a, b changes
    static int i;
    ntt::init(n);
    ntt::dft(a);
    ntt::dft(b);
    re (i, 0, n)
        a[i] = (ll)a[i] * b[i] % mo;
    ntt::idft(a);
}
// n must be 2^k above
 
int main() {
    static int i, n, p, l, f[N], g[N], gi[N];
    static ll inv[N], faci[N];
    scanf("%d", &n);  // it raises RE to use fread ioo
    if (n <= 1) {
        puts("1");
        return 0;
    }
    faci[0] = faci[1] = inv[1] = 1;
    rep (i, 2, n) {
        inv[i] = (mo - mo / i) * inv[mo % i] % mo;
        faci[i] = faci[i - 1] * inv[i] % mo;
    }
    g[0] = 1;
    rep (i, 1, n) {
        f[i] = qpow(2, (((ll)i * (i - 1)) >> 1) % (mo - 1));  // use mo-1
        g[i] = f[i] * faci[i] % mo;
        f[i] = f[i] * faci[i - 1] % mo;
    }
    p = n + 1;
    for (l = 1; l < p; l <<= 1);
    pinv(g, l, gi);
    pmul(f, gi, l << 1);
    printf("%d\n", (int)((ll)f[n] * qpow(faci[n - 1], mo - 2) % mo));
 
    return 0;
}
