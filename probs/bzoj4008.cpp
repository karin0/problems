#include <cstdio>
#include <cstring>

const int MAXN = 223, MAXM = 136;

int n, m, v[MAXN];
double p[MAXN], q[MAXN], f[MAXN][MAXM];


int main() {
    int t, i, j;
    double k;
    scanf("%d\n", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        for (i = 1; i <= n; ++i)
            scanf("%lf%d", p + i, v + i), q[i] = 0;
        
        memset(f, 0, sizeof(f)); 
        f[1][m] = 1;
        for (i = 1; i <= n; ++i) {
            k = 1;
            for (j = 0; j <= m; ++j) {
                f[i + 1][j] += f[i][j] * k;
                if (j)
                    f[i + 1][j - 1] += f[i][j] * (1 - k);
                q[i] += f[i][j] * (1 - k);
                k *= (1 - p[i]);
            }
        }
        k = 0;
        for (i = 1; i <= n; ++i)
            k += q[i] * v[i];
        printf("%.10lf\n", k);
    }
    
    return 0;
}
