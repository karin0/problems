#include <cstdio>

int main() {
    static int i, n = 3000000;
    static long long res, x;
    scanf("%lld", &res);
    for (i = 1; i < n; ++i)
        scanf("%lld", &x), res ^= x;
    printf("%lld\n", res);
    return 0;
}
