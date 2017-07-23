#include <cstdio>

int n, ans = 0;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        ans += n / i;
    printf("%d\n", ans);
    return 0;
}
