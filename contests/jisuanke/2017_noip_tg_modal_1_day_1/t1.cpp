#include <cstdio>
#include <algorithm>

const int MAXN = 2050;

int n, k, map[MAXN][MAXN], s[MAXN][MAXN];

inline int sum(int i, int j) {
    return s[i][j > 0 ? (j < n ? j : n) : 0];
}

int main() {
    int i, j, d, ans = 0, tans;
    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= n; ++j) {
            scanf("%d", &map[i][j]);
            s[i][j] = s[i][j - 1] + map[i][j];
        }
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= n; ++j) {
            tans = 0;
            for (d = 0; d <= k - 1 && i - d >= 1; ++d)
                tans += sum(i - d, j + k - d - 1) - sum(i - d, j - k + d);
            for (d = 1; d <= k - 1 && i + d <= n; ++d)
                tans += sum(i + d, j + k - d - 1) - sum(i + d, j - k + d);
            ans = std::max(ans, tans);
        }
    }
    printf("%d\n", ans);

    return 0;
}
