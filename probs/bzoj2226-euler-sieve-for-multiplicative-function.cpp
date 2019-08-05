#include <cstdio>

typedef long long ll;
const int N = 1000003;
int pri[N], phi[N], pcnt;
ll f[N];
bool np[N];
void sieve() {
    static const int n = 1000000;
    static int i, j;
    static ll v;
    phi[1] = 1;
    for (i = 2; i <= n; ++i) {
        if (!np[i])
            pri[++pcnt] = i, phi[i] = i - 1;
        for (j = 1; j <= pcnt && (v = (ll)i * pri[j]) <= n; ++j) {
            np[v] = true;
            if (i % pri[j] == 0) {
                phi[v] = pri[j] * phi[i];
                break;
            }
            phi[v] = phi[i] * (pri[j] - 1);
        }
    }
    for (i = 1; i <= n; ++i)
        for (j = i; j <= n; j += i)
            f[j] += (ll)phi[i] * i;
}

int main() {
    static int t, x;
    sieve();
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &x);
        printf("%lld\n", (f[x] + 1) * (ll)x / 2);
    }

    return 0;
}
