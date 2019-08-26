#include <cstdio>
#include <cmath>


int r, d, n, x, y, r0, cnt = 0;
int t1, t2;
int nor;
int main() {
    scanf("%d%d%d", &r, &d, &n);
    for (register int i = 1; i <= n; ++i) {
        scanf("%d%d%d", &x, &y, &r0);
        nor = x * x + y * y;
        t1 = r - d + r0;
        t2 = r - r0;
        if (nor >= t1 * t1 && nor <= t2 * t2)
            ++cnt;
    }
    printf("%d\n", cnt);

    return 0;
}
