#include <cstdio>
 
typedef long long ll;
 
const int p = 2333;
int c[p + 5][p + 5], s[p + 5][p + 5];
void init() {
    static int i, j;
    c[0][0] = 1;
    for (i = 1; i < p; ++i) {
        c[i][0] = 1;
        for (j = 1; j <= i; ++j) {
            c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
            if (c[i][j] >= p)
                c[i][j] -= p;
        }
    }
    for (i = 0; i < p; ++i) {
        s[i][0] = 1;
        for (j = 1; j < p; ++j) {
            s[i][j] = s[i][j - 1] + c[i][j];
            if (s[i][j] >= p)
                s[i][j] -= p;
        }
    }
}
int lucas(ll n, ll k) {
    if (k == 0)
        return 1;
    if (k > n)
        return 0;
    if (n < p && k < p)
        return c[n][k];
    return c[n % p][k % p] * lucas(n / p, k / p) % p;
}
int solve(ll n, ll k) {
    if (k == 0)
        return 1;
    if (k < 0)
        return 0;
    int nmp = n % p, kmp = k % p, res, tmp, tmp2;
    ll ndp = n / p, kdp = k / p;
    tmp = s[nmp][p - 1] - s[nmp][kmp];
    if (tmp < 0)
        tmp += p;
    tmp2 = solve(ndp, kdp - 1);
    res = s[nmp][kmp] * (tmp2 + lucas(ndp, kdp)) % p + tmp * tmp2 % p;
    if (res >= p)
        return res - p;
    return res;
}
 
inline int solve2(ll n, ll k) {
    static const int MOD = 2333;
    if (k < 0) return 0;
    if (k == 0) return 1;
 
    int s1 = solve(n / MOD, k / MOD - 1), s2 = (s1 + lucas(n / MOD, k / MOD)) % MOD;
 
    return ((s[n % MOD][k % MOD] * s2 % MOD + (s[n % MOD][MOD - 1] - s[n % MOD][k % MOD] + MOD) * s1) % MOD + MOD) % MOD;
}
int main() {
    static int t, kase;
    static ll n, k;
    init();
    scanf("%d", &t);
    for (kase = 0; kase < t; ++kase) {
        scanf("%lld%lld", &n, &k);
        printf("%d\n", solve(n, k));
    }
 
    return 0;
}
