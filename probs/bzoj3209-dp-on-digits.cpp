#include <cstdio>
#include <cstring>
#include <algorithm>

const int mo = 10000007, pmo = 9988440, W = 53;
typedef long long ll;

int qpow(ll a, ll x) {
    static ll res;
    for (res = 1; x; a = a * a % mo, x >>= 1)
        if (x & 1)
            res = res * a % mo;
    return res;
}
int main() {
    static ll n, c[W][W], cnt[W], ans; // 二进制表示中有 i 个 1 的数的个数
    static int i, j, m, t;
    scanf("%lld", &n);
    for (i = 1; (1ll << i) - 1 <= n; ++i);
    m = i - 1; // 最多可能有 m 个 1

    c[0][0] = 1;
    for (i = 1; i <= m; ++i) {
        c[i][0] = 1;
        for (j = 1; j <= i; ++j)
            c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % pmo;
    }

    for (i = m; i >= 0; --i)
        if ((n + 1) & (1ll << i)) {
            for (j = 0; j <= i; ++j)
                cnt[j + t] = (cnt[j + t] + c[i][j]) % pmo;
            ++t;
        }
    ans = 1;
    for (i = 2; i <= m; ++i)
        ans = ans * qpow(i, cnt[i]) % mo;
    printf("%lld\n", ans);
    return 0;
}
