#include <cstdio>
typedef long long LL;
const int MAXN = 1e5 + 10;
const int MOD = 1e9 + 7;

int n;
LL raw[MAXN];
LL qpow(LL x, LL p) {
    LL res = 1;
    for (; p; p >>= 1, x = (x * x) % MOD)
        if (p & 1)
            res = (res * x) % MOD;
    return res;
}

int main() {
    int q, i, opt, l, r;
    LL res, x;
    scanf("%d%d", &n, &q);
    for (i = 1; i <= n; ++i)
        scanf("%lld", raw + i); // pow 1
    while (q--) {
        scanf("%d%d%d%lld", &opt, &l, &r, &x);
        if (opt == 1) 
            for (i = l; i <= r; ++i)
                raw[i] = (raw[i] + x) % MOD;
        else if (opt == 2)
            for (i = l; i <= r; ++i)
                raw[i] = x;
        else {
            res = 0;
            for (i = l; i <= r; ++i)
                res = (res + qpow(raw[i], x)) % MOD;
            printf("%lld\n", res);
        }
    }
    return 0;
}
