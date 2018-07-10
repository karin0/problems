// 7ms!
#include <cstdio>
#define MAXN 105
#define MOD 9999973

inline int cx2(int x) {
    return (x * (x - 1)) >> 1;
}

int main() {
    static int n, m, i, a, b, c, ans;
    scanf("%d%d", &n, &m);
    // C(n, k) + C(n, k + 1) = C(n + 1, k + 1)
    // C(n, k + 1) = C(n, k) * (n - k) / (k + 1)
    // But we do not need this.
    if (n == 1) { 
        printf("%d\n", (1 + m + cx2(m)) % MOD);
        return 0;
    }
    static long long f[2][MAXN][MAXN];
    f[0][0][0] = 1;
    f[0][1][0] = m;
    f[0][2][0] = cx2(m) % MOD;
    for (i = 2; i <= n; ++i) { // Considering the previous i lines
        for (a = 0; a <= m; ++a) { // a cols have 1 goods
            for (b = 0; b <= m - a; ++b) {// b cols have 2 goods, so m - a - b lines have no goods
                c = m - a - b;
                f[1 ^ (i & 1)][a][b] = (
                  f[i & 1][a][b] +                        // 第 i 行不放
    (a < 1 ? 0 : (f[i & 1][a - 1][b] * (c + 1) )) +       // 在 0 列放 1 个
    (b < 1 ? 0 : (f[i & 1][a + 1][b - 1] * (a + 1) )) +   // 在 1 列放 1 个
    (a < 2 ? 0 : (f[i & 1][a - 2][b] * cx2(c + 2) )) +    // 在 0, 0 列放 2 个
    (b < 1 ? 0 : (f[i & 1][a][b - 1] * a * (c + 1) )) +   // 在 0, 1 列放 2 个
    (b < 2 ? 0 : (f[i & 1][a + 2][b - 2] * cx2(a + 2) )) // 在 1, 1 列放 2 个
                 ) % MOD;
            }
        }
    }
    n = 1 ^ (n & 1);
    for (a = 0; a <= m; ++a) // a cols have 1 goods
        for (b = 0; b <= m - a; ++b) { // b cols have 2 goods, so m - a - b lines have no goods
            ans += f[n][a][b];
            if (ans > MOD)
                ans -= MOD;
        }
    printf("%d\n", ans);
    return 0;
}
