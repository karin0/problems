#include <cstdio>

typedef unsigned int uint;
typedef unsigned long long ull;

uint phi(uint x) {
    static uint d, res;
    for (res = x, d = 2; d * d <= x; ++d) {
        if (x % d == 0) {
            res -= res / d;
            while (x % d == 0)
                x /= d;
        }
    }
    if (x > 1)
        return res - res / x;
    return res;
}

int main() {
    uint n, d, e;
    ull ans = 0;
    scanf("%d", &n);
    for (d = 1; d * d < n; ++d)
        if (n % d == 0)
            e = n / d, ans += (ull)d * phi(e) + (ull)e * phi(d);
    if (d * d == n)
        ans += (ull)d * phi(d);
    printf("%lld\n", ans);

    return 0;
}
