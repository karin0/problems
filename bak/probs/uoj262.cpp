#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAXN = 2005, MAXV = 305, INF = 0x3f3f3f3f;

int n, m, v;
int c[MAXN], d[MAXN], cost[MAXN][MAXN];
double p[MAXN], f[MAXN][MAXN][2];

int main() {
    int e, x, y, w, i, j, k;
    double ans = (double)INF;
    scanf("%d%d%d%d", &n, &m, &v, &e);
    for (i = 1; i <= n; ++i)
        scanf("%d", c + i);
    for (i = 1; i <= n; ++i)
        scanf("%d", d + i);
    for (i = 1; i <= n; ++i)
        scanf("%lf", p + i);
    memset(cost, 0x3f, sizeof(cost));
    for (i = 1; i <= e; ++i) {
        scanf("%d%d%d", &x, &y, &w);
        cost[x][y] = cost[y][x] = std::min(cost[x][y], w); // 重边
    }
    for (i = 1; i <= v; ++i)
        cost[i][i] = 0;
    for (k = 1; k <= v; ++k)
        for (i = 1; i <= v; ++i)
            for (j = 1; j <= v; ++j)
                cost[i][j] = std::min(cost[i][j], cost[i][k] + cost[k][j]);
   
    f[1][0][1] = INF;

    for (i = 2; i <= n; ++i) {
        for (j = 0; j <= m; ++j) {
            // f[i][j][x]: 前 i 个时段，申请了 j 次，第 i 个时段没有/有（x）申请最小的期望代价
            f[i][j][0] = std::min(
                    f[i - 1][j][0] + cost[c[i - 1]][c[i]], 
                    f[i - 1][j][1] + cost[d[i - 1]][c[i]] * p[i - 1] + cost[c[i - 1]][c[i]] * (1 - p[i - 1])
                    );
            f[i][j][1] = (j > 0) ?
                std::min(
                    f[i - 1][j - 1][0] + cost[c[i - 1]][d[i]] * p[i] + cost[c[i - 1]][c[i]] * (1 - p[i]), 
                    f[i - 1][j - 1][1] + 
                        cost[d[i - 1]][d[i]] * p[i - 1] * p[i] + 
                        cost[d[i - 1]][c[i]] * p[i - 1] * (1 - p[i]) +
                        cost[c[i - 1]][d[i]] * (1 - p[i - 1]) * p[i] +
                        cost[c[i - 1]][c[i]] * (1 - p[i - 1]) * (1 - p[i])
                    ) : INF;

        }
    }
    for (j = 0; j <= m; ++j)
        ans = std::min(ans, std::min(f[n][j][1], f[n][j][0]));

    printf("%.2lf\n", ans); 
    return 0;
}
