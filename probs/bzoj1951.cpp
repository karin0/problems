// the best template on number theory ever
#include <cstdio>
#include <cmath>

typedef long long ll;
const ll MOD = 999911659, m[5] = {0, 2, 3, 4679, 35617}, mc = 4, M = 35617;

inline ll qpow(ll x, ll p, ll mo) {
    static ll res;
    for (res = 1; p; p >>= 1, x = x * x % mo)
        if (p & 1)
            res = res * x % mo;
    return res;
}
ll fac[5][M + 5], fac_inv[5][M + 5];
inline void init() {
    static int i, j;
    static ll *fa, *fi, mo;
    for (j = 1; j <= mc; ++j) {
        mo = m[j];
        fa = fac[j], fi = fac_inv[j];
        fa[0] = 1;
        for (i = 1; i < mo; ++i)
            fa[i] = fa[i - 1] * i % mo;
        fi[mo - 1] = qpow(fa[mo - 1], mo - 2, mo);
        for (i = mo - 2; i >= 0; --i)
            fi[i] = fi[i + 1] * (i + 1) % mo;
        /*
         * Pepcy_Ch's method
        fi[1] = 1;
        for (i = 2; i < mo; ++i)
            fi[i] = (mo - mo / i) * fi[mo % i] % mo;
        fi[0] = 1;
        for (i = 1; i <= mo; ++i)
            fi[i] = fi[i] * fi[i - 1] % mo;
        */
    }
}
inline ll comb(ll n, ll k, int j) {
    if (n < k)
        return 0;
    ll mo = m[j];
    if (n < mo && k < mo)
        return fac[j][n] * fac_inv[j][k] % mo * fac_inv[j][n - k] % mo;
    return comb(n / mo, k / mo, j) * comb(n % mo, k % mo, j) % mo;
}
ll a[5];
inline ll crt() {
    static ll res, mm;
    static int i;
    res = 0;
    for (i = 1; i <= mc; ++i) {
        mm = (MOD - 1) / m[i];
        res = (res + a[i] * mm % (MOD - 1) * qpow(mm, m[i] -  2, m[i]) % (MOD - 1)) % (MOD - 1);
    }
    return (res % (MOD - 1) + (MOD - 1)) % (MOD - 1);
}
ll n, g;
inline ll calc() { // g ^ sum {c(n, k) | k | n} mod MOD
    static int d, i;
    g %= MOD;
    if (g == 0)
        return 0;
    init();
    for (d = 1; d * d <= n; ++d) {
        if (n % d == 0) {
            for (i = 1; i <= mc; ++i)
                a[i] = (a[i] + comb(n, d, i)) % m[i];
            if (d * d < n)
                for (i = 1; i <= mc; ++i)
                    a[i] = (a[i] + comb(n, n / d, i)) % m[i];
        }
    }
    return qpow(g, crt(), MOD);
}

int main() {
    scanf("%lld%lld", &n, &g);
    printf("%lld\n", calc());

    return 0;
}
