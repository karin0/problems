#include <cstdio>

int main() {
    long long n;
    scanf("%lld", &n);
    printf("%.9lf\n", n * (n + 1) / (double)(2 * (2 * n - 1)));
    return 0;
}
