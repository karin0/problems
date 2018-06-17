#include <cstdio>
#include <algorithm>

const int T = 100005;
bool np[T];
int pri[T], phi[T], pcnt;
typedef long long ll;
void sieve(int n) {
    static int i, j;
    static ll v;
    np[0] = np[1] = true;
    phi[1] = 1;
    for (i = 2; i <= n; ++i) {
        if (!np[i])
            pri[pcnt++] = i, phi[i] = i - 1;
        for (j = 0; j < pcnt && (v = (ll)i * pri[j]) <= n; ++j) {
            np[v] = true;
            if (i % pri[j] == 0) {
                phi[v] = phi[i] * pri[j];
                break;
            }
            phi[v] = phi[i] * (pri[j] - 1);
        }
    }
    for (i = 2; i <= n; ++i)
        phi[i] += phi[i - 1];
}
ll calc(int n, int m) {
    static int i, r, x, y;
    static ll res;
    for (res = 0, i = 1; i <= n; i = r + 1) {
        x = n / i, y = m / i;
        r = std::min(n / x, m / y);
        res += (ll)(phi[r] - phi[i - 1]) * x * y;
    }
    return res;
}
int main() {
    static int n, m;
    scanf("%d%d", &n, &m);
    if (n > m)
        std::swap(n, m);
    sieve(n);
    printf("%lld\n", 2 * calc(n, m) - (ll)n * m);
    return 0;
}
