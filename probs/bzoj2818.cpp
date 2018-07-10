#include <cstdio>

const int MAXN = 10000005;

bool np[MAXN];
int pri[MAXN], pcnt;
long long phi[MAXN], ans;
inline void sieve(int n) {
    static int i, j;
    static long long v;
    np[0] = np[1] = true;
    phi[1] = 1;
    for (i = 2; i <= n; ++i) {
        if (!np[i])
            pri[++pcnt] = i, phi[i] = i - 1;
        for (j = 1; j <= pcnt; ++j) {
            v = (long long)pri[j] * i;
            if (v > n)
                break;
            np[v] = true;
            if (i % pri[j] == 0) {
                phi[v] = phi[i] * pri[j];
                break;
            } else
                phi[v] = phi[i] * (pri[j] - 1);
        }
    }

}

int main() {
    static int n, i;
    scanf("%d", &n); // a
    sieve(n);
    for (i = 2; i <= n; ++i)
        phi[i] += phi[i - 1];
    for (i = 1; i <= pcnt; ++i)
        ans += phi[n / pri[i]];
    ans <<= 1;
    ans -= pcnt;
    printf("%lld\n", ans);
    
    return 0;
}
