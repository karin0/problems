#include <cstdio>

const int MAXN = 223, MAXM = 136;

int n, m;
double p[MAXN], f[MAXN][MAXM], g[MAXN], h[MAXN], a[MAXN][MAXM];
int v[MAXN];


int main() {
    int t, i, j, x, y;
    double res, ans;
    scanf("%d\n", &t);
    while (t--) {
        ans = 0;
        scanf("%d%d", &n, &m);
        for (x = 1; x <= n; ++x)
            scanf("%lf%d", p + x, v + x);
        
        for (y = 0; y <= m; ++y)
            a[0][y] = 1;
        for (x = 1; x <= n; ++x) {
            g[0] = 1;
            h[0] = 0;
            a[x][0] = 1;
            res = 0.0;
            for (y = 1; y <= m; ++y) {
                f[x][y] = a[x - 1][y - 1] * g[y - 1] * p[x];
                res += f[x][y];
                g[y] = g[y - 1] * (1 - f[x][y]);
                h[y] = h[y - 1] + f[x][y];
                a[x][y] = a[x - 1][y] * (g[y] * (1 - p[x]) + h[y]);
            }
            printf("[%lf]\n", res);
            ans += v[x] * res;
        }

    }
    
    printf("%.10lf\n", ans);
    return 0;
}
