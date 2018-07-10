#include <cstdio>
#include <algorithm>

const int MAXN = 50003, MAXM = 1003, MOD = 10007;
int n, m, a[MAXN], sum[MAXN], g[MAXN];
bool check(int x) {
    static int i, s, cnt;
    s = 0, cnt = 1;
    for (i = 1; i <= n; ++i) {
        s += a[i];
        if (s > x) {
            s = a[i];
            if (s > x)
                return false;
            ++cnt;
            if (cnt > m)
                return false;
        }
    }
    return true;
}
int f[MAXN], sf[MAXN];
// f[i][j] = sum{f[k][j - 1] | sum{a[x] | k <= x < i} <= R, 1 <= k < i}
int main() {
    static int i, j, l, len, x, ans, r;
    scanf("%d%d", &n, &m);
    ++m;
    for (i = 1; i <= n; ++i)
        scanf("%d", a + i), sum[i] = sum[i - 1] + a[i];
    l = 0, r = sum[n];
    while (r - l > 1) {
        x = (l + r) >> 1;
        if (check(x))
            r = x;
        else
            l = x;
    }
    len = r;/*
    for (i = 1; i <= n; ++i) {
        f[i][1] = (sum[i] <= len);
        f[i][2] = f[i - 1][1];
        l = std::min(i, m);
        res = 0;
        for (j = 3; j <= l; ++j) {
            for (k = i - 1; k >= 1; --k) {
                if (sum[i - 1] - sum[k - 1] > len)
                   break;
                f[i][j] = (f[i][j] + f[k][j - 1]) % MOD;
            }
            res = (res + f[i][j]) % MOD;
        }
        if (sum[n] - sum[i - 1] <= len)
            ans = (ans + res) % MOD;
    }*/
    for (i = 1; i <= n; ++i) {
        f[i] = (sum[i] <= len);
        l = 1, r = i - 1;
        while (r - l > 1) {
            x = (l + r) >> 1;
            if (sum[i - 1] - sum[x - 1] <= len)
                r = x;
            else
                l = x;
        }
        g[i] = r;
        if (sum[n] - sum[i - 1] <= len)
            ans = (ans + f[i]) % MOD;
    }
    for (i = n; i >= 1; --i) {
        f[i] = f[i - 1];
        sf[i] = (sf[i + 1] + f[i]) % MOD;
        if (sum[n] - sum[i - 1] <= len)
            ans = (ans + f[i]) % MOD;
    }
    for (j = 3; j <= m; ++j) {
        for (i = n; i >= 1; --i) {
            if (j > i) {
                f[i] = 0;
                continue;
            }
            f[i] = (sf[g[i]] - sf[i] + MOD) % MOD;
            if (sum[n] - sum[i - 1] <= len)
                ans = (ans + f[i]) % MOD;
        }
        for (i = n; i >= 1; --i)
            sf[i] = (sf[i + 1] + f[i]) % MOD;
    }
    printf("%d %d\n", len, ans);
    return 0; 
}
