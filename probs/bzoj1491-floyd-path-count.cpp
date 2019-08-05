#include <cstdio>
#include <cstring>
 
typedef long long ll;
const int MAXN = 103;
int n, m, d[MAXN][MAXN];
ll f[MAXN][MAXN];
 
void floyd() {
    static int i, j, k;
    for (k = 1; k <= n; ++k) {
        for (i = 1; i <= n; ++i) {
            for (j = 1; j <= n; ++j) {
                if (d[i][k] + d[k][j] < d[i][j])
                    d[i][j] = d[i][k] + d[k][j], f[i][j] = f[i][k] * f[k][j];
                else if (d[i][k] + d[k][j] == d[i][j])
                    f[i][j] += f[i][k] * f[k][j];
            }
        }
    }
}
 
int main() {
    static int i, u, v, w;
    static double ans;
    scanf("%d%d", &n, &m);
    memset(d, 0x3f, sizeof(d));
    for (i = 1; i <= m; ++i) {
        scanf("%d%d%d", &u, &v, &w);
        d[u][v] = w, d[v][u] = w;
        f[u][v] = f[v][u] = 1;
    }
    for (i = 1; i <= n; ++i)
        d[i][i] = 0; // f[i][i] = 1;
    floyd();
    for (i = 1; i <= n; ++i) {
        ans = 0.0;
        for (u = 1; u <= n; ++u) {
            if (u != i) {
                for (v = 1; v <= n; ++v) {
                    if (v != i && d[u][i] + d[i][v] == d[u][v])
                        ans += f[u][i] * f[i][v] / (double)f[u][v];
                }
            }
        }
        printf("%.3lf\n", ans);
    }
 
    return 0;
}
