#include <cstdio>
typedef long long LL;
const LL MOD = 998244353;

inline LL sa(LL x) { // sa(x) = sum{A(x - 1, i) | 2 <= i <= x - 1}
    LL res = 0, a = x - 1;
    for (int i = 2; i <= x - 1; ++i) {
        a = (a * ((x - 1 - i + 1) % MOD)) % MOD;
        res = (res + a) % MOD;
    }
    return res;
}
inline LL sg(LL x) { 
    // g(n, x) = A(n - 3, x - 2) * (x - 1) 
    // sg(x) = sum{g(x, i) | 2 <= i <= x - 1}
    //          = sum{A(x - 3, i - 2) * (i - 1) | 2 <= i <= x - 1}
    LL res = 1, a = 1;
    for (int i = 3; i <= x - 1; ++i) {
        a = (a * (x - 3 - i + 3) % MOD) % MOD;
        res = (res + a * (i - 1) % MOD) % MOD;
    }
    return res;
}

inline LL ans(LL x) { // ans(x) = sa(x) / 2 - sg(x)
    return (sa(x) / 2 - sg(x) + MOD) % MOD;
}

int main() {
    int q;
    LL n;
    scanf("%d", &q);
    while (q--) {
        scanf("%lld", &n);
        printf("%lld\n", ans(n));
    }

    return 0;
}
