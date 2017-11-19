#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAXN = 10005, MAXM = 1005, INF = 0x3f3f3f3f;
int n, m, k, up[MAXN], down[MAXN], l[MAXN], h[MAXN];
inline void upd(int &a, const int x) {
    if (x < a)
        a = x;
}
int main() {
    static int i, j, f[MAXN][MAXM], ans, cnt;
    static bool fail;
    scanf("%d%d%d", &n, &m, &k);
    for (i = 0; i < n; ++i) {
        scanf("%d%d", up + i, down + i);
        // l[j] = 0;
        h[i] = m + 1;
    }
    h[n] = m + 1; // ***
    for (i = 0; i < k; ++i) {
        scanf("%d", &j);
        scanf("%d%d", l + j, h + j);
    }
    memset(f, 0x3f, sizeof(f));
    for (j = 0; j <= m; ++j)
        f[0][j] = 0;
    for (i = 0; i <= n; ++i) {
        fail = true;
        for (j = 0; j <= m; ++j) { // 高度
            if (i > 0)
                upd(f[i][std::min(m, j + up[i - 1])], f[i][j] + 1);
            if (i > 0 && j + down[i - 1] <= m)
                upd(f[i][j], f[i - 1][j + down[i - 1]]);
            // printf("f[%d][%d] = %d (Good: %d)\n", i, j, f[i][j], j > l[i] && j < h[i]);
            if (f[i][j] >= INF)
                continue;
            if (j > l[i] && j < h[i]) {
                fail = false;
                upd(f[i + 1][std::min(m, j + up[i])], f[i][j] + 1);
            } else {
                f[i][j] = INF;
                f[i][j] = INF; 
            }
        }
        if (fail) {
            printf("0\n%d\n", cnt);
            return 0;
        }
        cnt += h[i] <= m;
    }
    ans = INF;
    for (j = l[n] + 1; j < h[n]; ++j)
        ans = std::min(ans, f[n][j]);
    printf("1\n%d\n", ans);

    return 0;
}
