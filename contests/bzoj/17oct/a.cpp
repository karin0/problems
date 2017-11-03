#include <cstdio>
#include <math.h>

const int MAXN = 100005;
int a[MAXN], b[MAXN];

int main() {
    static int t, n, ks, i, x;
    static bool flag;
    scanf("%d", &t);
    for (ks = 1; ks <= t; ++ks) {
        scanf("%d", &n);
        for (i = 1; i <= n; ++i)
            scanf("%d", a + i);
        for (i = 1; i <= n; ++i)
            scanf("%d", b + i);
        flag = false;
        for (i = 2; i < n; ++i) {
            if (a[i] + a[i - 1] + a[i + 1] == b[i] + b[i - 1] + b[i + 1]) {
                flag = true;
                break;
            }
        }
        puts(flag ? "YES" : "NO");
    }
    return 0;
}
