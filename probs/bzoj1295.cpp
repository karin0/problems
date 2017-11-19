#include <cstdio>
#include <cstring>
#include <math.h>
#include <algorithm>

const int MAXN = 35;
int n, m, t;
bool a[MAXN][MAXN];
int sx, sy;
int dx[4] = {0,  0, 1, -1},
    dy[4] = {1, -1, 0,  0};
double ans;
inline int sq(int x) {
    return x * x;
}
bool vis[MAXN][MAXN];
int ach[MAXN][MAXN];
void dfs(int x, int y, int p) {
    int nx, ny, np, k;
    ans = std::max(ans, sqrt(sq(x - sx) + sq(y - sy)));
    vis[x][y] = true;
    ach[x][y] = std::max(ach[x][y], p);
    for (k = 0; k < 4; ++k) {
        nx = x + dx[k];
        ny = y + dy[k];
        if (nx < 1 || nx > n || ny < 1 || ny > m)
            continue;
        np = p - a[nx][ny];
        if (np >= 0 && ((!vis[nx][ny]) || ach[nx][ny] < np))
            dfs(nx, ny, np);
    }
}

int main() {
    static int i, j;
    static char line[MAXN];
    scanf("%d%d%d", &n, &m, &t);
    for (i = 1; i <= n; ++i) {
        scanf("%s", line + 1);
        for (j = 1; j <= m; ++j)
            a[i][j] = line[j] == '1';
    }
    ans = 0.0;
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= m; ++j)
            if (t >= a[i][j]) {
                sx = i, sy = j;
                memset(vis, 0, sizeof(vis));
                memset(ach, 0, sizeof(ach));
                dfs(i, j, t - a[i][j]);
            }

    printf("%.6lf\n", ans);
    return 0;
}
