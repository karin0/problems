#include <cstdio>
#include <algorithm>

typedef long long ll;
const int n = 50000;
bool np[n + 5];
int pri[n + 5], mu[n + 5], pcnt;
void sieve() {
    static int i, j;
    static ll v;
    mu[1] = 1;
    for (i = 2; i <= n; ++i) {
        if (!np[i])
            pri[++pcnt] = i, mu[i] = -1;
        for (j = 1; j <= pcnt; ++j) {
            v = (ll)i * pri[j];
            if (v > n)
                break;
            np[v] = true;
            if (i % pri[j] == 0) {
                mu[v] = 0;
                break;
            }
            mu[v] = -mu[i];
        }
    }
    for (i = 2; i <= n; ++i)
        mu[i] += mu[i - 1];
}

int main() {
    static int m, a, b, c, d, k, i, ni, da, db;
    static ll res;
    sieve();
    scanf("%d", &m);
    while (m--) {
        res = 0;
        scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
        if (b < a)
            std::swap(a, b);
        a /= k, b /= k;
        for (i = 1; i <= a; i = ni + 1) {
            da = a / i, db = b / i;
            ni = std::min(a / da, b / db);
            res += (ll)(mu[ni] - mu[i - 1]) * da * db;
        }
        printf("%lld\n", res);
    }
    return 0;
}

