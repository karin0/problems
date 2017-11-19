#include <cstdio>
#include <algorithm>

const int MOD = 12345678, MAXN = 153, MAXK = 23;

int n, m, p;
int f[MAXN][MAXN][MAXK][MAXK];

inline void update(int i, int j, int k, int l, int v) {
    if (0 <= k && k <= p && 0 <= l && l <= p) {
        int &ff = f[i][j][k][l];
        ff += v;
        if (ff > MOD)
            ff -= MOD;
    }
}

int main() {
    int i, j, k, l, ans = 0;
    scanf("%d%d%d", &n, &m, &p); // n 个 1, m 个 -1
    
    f[0][0][0][0] = 1;
    // f[1][0][1][0] = 1;
    // f[0][1][0][0] = 1;

    for (i = 0; i <= n; ++i)
        for (j = 0; j <= m; ++j)
            for (k = 0; k <= p; ++k) // - 最小后缀和（含空后缀）
                for (l = 0; l <= p; ++l) { // 最大后缀和
                    const int &ff = f[i][j][k][l];
                    update(i + 1, j, std::max(k - 1, 0), l + 1, ff);
                    update(i, j + 1, k + 1, std::max(l - 1, 0), ff);
                }

    for (k = 0; k <= p; ++k)
        for (l = 0; l <= p; ++l) {
            ans += f[n][m][k][l]; // 而不是取 max
            if (ans > MOD)
                ans -= MOD;
        }
    printf("%d\n", ans);
    return 0;
}
