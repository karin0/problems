#include <cstdio>

const int MAXN = 10005;

int n, a[MAXN], b[MAXN];

int main() {
    int i, ans = 0;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i)
        scanf("%d", b + i);
    
    if (n == 1) {
        printf("1\n");
    } else {
        for (a[1] = 0; a[1] <= b[1]; ++a[1]) {
            a[2] = b[1] - a[1];
            for (i = 3; i <= n; ++i)
                a[i] = b[i - 1] - a[i - 2] - a[i - 1];
            if (b[n] == a[n - 1] + a[n])
                ++ans;
        }
        printf("%d\n", ans);
    }

    return 0;
}
