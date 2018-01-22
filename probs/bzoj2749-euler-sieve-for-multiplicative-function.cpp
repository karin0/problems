#include <cstdio>

typedef long long ll;
const int N = 100003;
int pri[N], f[N], pcnt;
bool np[N];
void sieve() {
    static const int n = 100000;
    static int i, j;
    static ll v;
    f[1] = 0;
    for (i = 2; i <= n; ++i) {
        if (!np[i])
            pri[++pcnt] = i, f[i] = (i == 2) ? 1 : f[i - 1];
        for (j = 1; j <= pcnt && (v = (ll)i * pri[j]) <= n; ++j) {
            np[v] = true;
            f[v] = f[i] + f[pri[j]];
            if (i % pri[j] == 0)
                break;
        }
    }
}

int main() {
    static int p, q, m, t;
    static ll ans;
    static bool even;
    scanf("%d", &t);
    sieve();
    while (t--) {
        scanf("%d", &m);
        even = false;
        ans = 0;
        while (m--) {
            scanf("%d%d", &p, &q);
            even |= p == 2;
            ans += (ll)f[p] * q;
        }
        printf("%lld\n", ans + !even);
    }

    return 0;
}
