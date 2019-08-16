#include <akari>

IO<1000000, 10> io;

cint N = 10000002, M = 3002, mo = 998244353;

int fa[N], fi[N], f[N], g0[M], g1[M];
inline int qpow(ll a, int n) {
    ll res = 1;
    for (; n; n >>= 1, a = a * a % mo)
        if (n & 1)
            res = res * a % mo;
    return res;
}
inline int binom(ll n, int k) {
    if (n < 0 || k < 0 || k > n)
        return 0;
    return (ll)fa[n] * fi[k] % mo * fi[n - k] % mo;
}

struct S {
    int t, p;
    bool operator < (const S &rhs) const {
        return t < rhs.t;
    }
} a[M];

int main() {
    int n, d, m;
    io >> n >> d >> m;
    rep (i, 1, m)
        io >> a[i].t >> a[i].p;

    fa[0] = 1;
    rep (i, 1, n) 
        fa[i] = (ll)fa[i - 1] * i % mo;
    fi[n] = qpow(fa[n], mo - 2);
    per (i, n, 1)
        fi[i - 1] = (ll)fi[i] * i % mo;

    f[0] = 1; // ***
    int fs = 0;
    rep (i, d, n) {
        fs += f[i - d];
        if (fs >= mo)
            fs -= mo;
        f[i] = fs;
        // ccc(i, f[i]);
    }
    std::sort(a + 1, a + m + 1);

    g0[0] = 1;
    int ans = f[n];
    rep (i, 1, m) {
        int g0i = 0, g1i = 0, ait = a[i].t, aip = a[i].p;
        re (j, 0, i) {
            int t = ait - a[j].t;
            if (t <= 0) continue;
            int p = aip - a[j].p;
            if (p <= 0) continue;
            ll r = binom(p - (ll)d * t + t - 1, t - 1);
            g0i = (g0i + g1[j] * r) % mo;
            g1i = (g1i + g0[j] * r) % mo;
        }
        g0[i] = g0i;
        g1[i] = g1i;
        int t = g0i - g1i;
        if (t < 0)
            t += mo;
        ans = (ans + (ll)t * f[n - aip]) % mo;
    }

    io << ans daze;
    
    return 0;
}
