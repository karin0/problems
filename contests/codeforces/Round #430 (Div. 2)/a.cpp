#include <cstdio>

long long l, r, x, y, k;
int main() {
    // l / y <= k <= r / x
    scanf("%I64d%I64d%I64d%I64d%I64d", &l, &r, &x, &y, &k);
    printf((k * y >= l && k * x <= r) ? "YES\n" : "NO\n");

    return 0;
}
