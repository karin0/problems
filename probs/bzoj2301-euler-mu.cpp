#include <cstdio>
#include <algorithm>

typedef long long ll;
const int N = 50003;
bool np[N];
int n, pri[N], mu[N], pcnt, k;
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
ll solve(int a, int b) {
    static ll res;
    static int i, ni, da, db;
    res = 0;
    if (b < a)
        std::swap(a, b);
    a /= k, b /= k;
    for (i = 1; i <= a; i = ni + 1) {
        da = a / i, db = b / i;
        ni = std::min(a / da, b / db);
        res += (ll)(mu[ni] - mu[i - 1]) * da * db;
    }
    return res;
}

int main() {
    static int a, b, c, d, m;
    n = N;
    scanf("%d", &m);
    sieve();
    while (m--) {
        scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
        printf("%lld\n", solve(b, d) - solve(a - 1, d) - solve(b, c - 1) + solve(a - 1, c - 1));
    }
    return 0;
}

