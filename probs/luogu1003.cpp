#include <cstdio>
#define MAXN 10010

int n;
int a[MAXN], b[MAXN], g[MAXN], k[MAXN];
int main() {
    int x, y;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d%d%d%d", a + i, b + i, g + i, k + i);
    scanf("%d%d", &x, &y);
    for (int i = n; i >= 1; --i) {
        if (
                a[i] <= x            &&
                x <= a[i] + g[i]     &&
                b[i] <= y            &&
                y <= b[i] + k[i]
            ) {
            printf("%d\n", i);
            return 0;
        }
    }
    printf("-1\n");
    return 0;
}
