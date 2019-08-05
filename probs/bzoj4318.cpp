#include <cstdio>

const int MAXN = 1e5 + 5;
int n;
double p[MAXN], f[MAXN], e[MAXN], e2[MAXN]; 

int main() {
    int i;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i)
        scanf("%lf", p + i);
    
    for (i = 1; i <= n; ++i) {
        e[i] = (e[i - 1] + 1) * p[i];
        e2[i] = (e2[i - 1] + e[i - 1] * 2 + 1) * p[i];
        f[i] = f[i - 1] + (e2[i - 1] * 3 + e[i - 1] * 3 + 1) * p[i];
    }
    
    printf("%.1lf\n", f[n]);

    return 0;
}
