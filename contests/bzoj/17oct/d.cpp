#include <cstdio>
#include <math.h>

int main() {
    static int t, n, ks, i, x;
    static double s;
    static bool flag;
    scanf("%d", &t);
    for (ks = 1; ks <= t; ++ks) {
        scanf("%d", &n);
        flag = false;
        s = 0;
        for (i = 1; i <= n; ++i) {
            scanf("%d", &x);
            s += (double)1 / (double)x;
            if (s > 1 && fabs(s - 1.0) > 1e-6) {
                flag = true;
            }
        }
        puts(flag ? "NO" : "YES");
    }
    return 0;
}
