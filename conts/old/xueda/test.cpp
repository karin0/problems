#include <cstdio>

typedef long long ll;
int a[100000], n = 50000, MOD = 1000000007;
int res;
int main() {
    for (int i = 1; i <= n; ++i)
        a[i] = MOD - 1;
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j) {
            res += a[i] * a[j] % MOD;
            if (res >= MOD)
                res -= MOD;
        }
    printf("%d\n", res);
    
    return 0;
}
