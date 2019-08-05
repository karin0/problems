#include <cstdio>
#include <algorithm>

typedef long long ll;
const int N = 5000003, mo = 1000000007;
bool np[N];
int pri[N], mu[N], f[N], pcnt;
void sieve() {
    static const int n = 5000000;
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
    for (i = 2; i <= n; ++i) {
        mu[i] += mu[i - 1];
        (f[i] += f[i - 1]) %= mo;
    }
}
int k;
int calc(int n, int m) {
}

int main() {
    static int ks, n, m;
    sieve();
    scanf("%d%d", &ks, &k);
    while (ks--) {
        scanf("%d%d", &n, &m);
        printf("%d\n", calc(n, m));
    }
    return 0;
}

