#include <cstdio>

const int MAXN = 3000005;

long long n, p, inv[MAXN];

int main() {
    scanf("%lld%lld", &n, &p);
    inv[1] = 1;
    puts("1\n");
    for (int i = 2; i <= n; ++i)
        printf("%lld\n", inv[i] = (p - p / i) * inv[p % i] % p);
    return 0;
}
