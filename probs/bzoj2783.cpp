#include <cstdio>
#include <algorithm>

const int MAXN = 100005, MAXB = 17, INF = 0x7ffffffa;

int n, m, jmp[MAXN][MAXB], sum[MAXN][MAXB];

int main() {
    int i, j, x, y, ans = 0, pos, s;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i)
        scanf("%d", &x), sum[i][0] = x;
    for (i = 1; i < n; ++i)
        scanf("%d%d", &x, &y), jmp[y][0] = x;
    
    for (j = 1; j < MAXB; ++j)
        for (i = 2; i <= n; ++i)
            jmp[i][j] = jmp[jmp[i][j - 1]][j - 1];
    for (j = 1; j < MAXB; ++j)
        for (i = 1; i <= n; ++i)
            sum[i][j] = ((jmp[i][j] == 0) ? INF : (sum[i][j - 1] + sum[jmp[i][j - 1]][j - 1]));

    for (i = 1; i <= n; ++i) {
        pos = i, s = 0;
        while (s < m && pos > 0) {
            j = std::upper_bound(sum[pos] + 0, sum[pos] + MAXB, m - s) - sum[pos] - 1;
            if (j < 0)
                break;
            s += sum[pos][j];
            pos = jmp[pos][j];
        }
        // printf("[%d, %d]", i, s);
        if (s == m)
            ++ans;
    }

    printf("%d\n", ans);
    return 0;
}
