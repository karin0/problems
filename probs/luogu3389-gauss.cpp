#include <cstdio>
#include <cmath>
#include <algorithm>

const int N = 103;
const double eps = 1e-8;
double a[N][N];
bool gauss(int n) {
    static int i, j, k, p;
    static double t;
    for (i = 0; i < n; ++i) {
        p = i;
        for (j = i + 1; j < n; ++j)
            if (fabs(a[j][i]) > fabs(a[p][i]))
                p = j;
        if (fabs(a[p][i]) < eps)
            return false;
        if (p != i)
            for (j = i; j <= n; ++j)
                std::swap(a[i][j], a[p][j]);
        for (j = 0; j < n; ++j)
            if (i != j) {
                t = a[j][i] / a[i][i];
                for (k = n; k >= i; --k)
                    a[j][k] -= a[i][k] * t;
            }
    }
    return true;
}
int main() {
    static int n, i, j, x;
    scanf("%d", &n);
    for (i = 0; i < n; ++i)
        for (j = 0; j <= n; ++j)
            scanf("%d", &x), a[i][j] = x;
    if (gauss(n))
        for (i = 0; i < n; ++i)
            printf("%lf\n", a[i][n] / a[i][i]);
    else
        puts("No Solution");

    return 0;
}
