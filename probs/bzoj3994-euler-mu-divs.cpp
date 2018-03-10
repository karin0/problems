#include <cstdio>
#include <algorithm>

int N = 1;
const int T = 50005;
bool np[T];
int pri[T], mu[T], pcnt;
typedef long long ll;
void sieve() {
    static int i, j;
    static ll v;
    np[0] = np[1] = true;
    mu[1] = 1;
    for (i = 2; i <= N; ++i) {
        if (!np[i])
            pri[pcnt++] = i, mu[i] = -1;
        for (j = 0; j < pcnt && (v = (ll)i * pri[j]) <= N; ++j) {
            np[v] = true;
            if (i % pri[j] == 0) {
                mu[v] = 0;
                break;
            }
            mu[v] = -mu[i];
        }
    }
    for (i = 2; i <= N; ++i)
        mu[i] += mu[i - 1];
}
ll fcalc(int n) {
    static int i, r, x;
    static ll res;
    for (res = 0, i = 1; i <= n; i = r + 1) {
        x = n / i;
        r = n / x;
        res += (ll)x * (r - i + 1);
    }
    return res;
}
ll f[T];
ll calc(int n, int m) {
    static int i, r, x, y;
    static ll res;
    if (n > m)
        std::swap(n, m);
    for (res = 0, i = 1; i <= n; i = r + 1) {
        x = n / i, y = m / i;
        r = std::min(n / x, m / y);
        res += (ll)(mu[r] - mu[i - 1]) * f[x] * f[y];
    }
    return res;
}
int main() {
    static int t, i, ns[T], ms[T];
    scanf("%d", &t);
    for (i = 0; i < t; ++i) {
        scanf("%d%d", &ns[i], &ms[i]);
        N = std::max(N, std::max(ns[i], ms[i]));
    }
    sieve(); // ***
    for (i = 1; i <= N; ++i)
        f[i] = fcalc(i);
    for (i = 0; i < t; ++i)
        printf("%lld\n", calc(ns[i], ms[i]));
    return 0;
}
