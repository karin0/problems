#include <cstdio>

const int MOD = 100003;
typedef long long ll;

inline ll qpow(ll x, ll p) {
    ll res = 1;
    for (; p; p >>= 1, x = x * x % MOD)
        if (p & 1)
            res = (res * x) % MOD;
    return res;
}

ll n, m;

int main() {
    scanf("%lld%lld", &m, &n);
    m %= MOD;
    // m ^ n - m * (m - 1) ^ (n - 1)
    printf("%lld\n", (qpow(m, n) + MOD - (m * qpow(m - 1, n - 1)) % MOD) % MOD);
    return 0;
}
