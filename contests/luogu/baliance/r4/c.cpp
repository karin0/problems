#include <cstdio>
#include <algorithm>

const int MAXN = 12;
int n, m, a[MAXN][MAXN], f[MAXN], g[MAXN], ans;
// f[i]: addition to a[1..n][j]
// g[j]: addition to a[i][1..m]
void dfs(int j) { // 枚举 f[]
    if (j > m) {
        int res = 0, cnt[3], x, i;
        for (i = 1; i <= n; ++i) {
            cnt[0] = 0;
            cnt[1] = 0;
            cnt[2] = 0;
            for (j = 1; j <= m; ++j) {
                x = a[i][j] + f[j];
                if (x <= 12)
                    ++cnt[x % 3];
            }
            res += std::max(cnt[0], std::max(cnt[1], cnt[2]));
        }
        ans = std::max(ans, res);
        return;
    }
    f[j] = 0;
    dfs(j + 1);
    f[j] = 1;
    dfs(j + 1);
    f[j] = 2;
    dfs(j + 1);
    // f[i] = t;
}

int main() {
    static int i, j;
    scanf("%d%d", &n, &m);
    if (m <= n) {
        for (i = 1; i <= n; ++i)
            for (j = 1; j <= m; ++j)
                scanf("%d", a[i] + j);
    } else {
        for (i = 1; i <= n; ++i)
            for (j = 1; j <= m; ++j)
                scanf("%d", a[j] + i);
        std::swap(n, m);
    }
    dfs(1);
    printf("%d\n", ans);
    return 0;
}
