#include <cstdio>
#include <algorithm>

typedef long long ll;
int main() {
    static ll n, k, i, ans, ni, t;
    scanf("%lld%lld", &n, &k);
    ans = n * k;
    n = std::min(n, k);
    for (i = 1; i <= n; i = ni + 1) {
        t = k / i;
        ni = std::min(n, k / t); // ***
        ans -= (i + ni) * (ni - i + 1) / 2 * t;
    }
    printf("%lld\n", ans);

    return 0;
}
