#include <cstdio>
#include <algorithm>

const int N = 1000004;
typedef long long ll;
bool np[N];
int pri[N], pcnt;
void sieve(const int n) {
    static int i, j;
    static ll v;
    np[0] = np[1] = true;
    for (i = 2; i <= n; ++i) {
        if (!np[i])
            pri[++pcnt] = i;
        for (j = 1; j <= pcnt; ++j) {
            v = (ll)i * pri[j];
            if (v > n)
                break;
            np[v] = true;
            if (i % pri[j] == 0) {
                break;
            }
        }
    }
}
int mpf(int x) {
    static int i, ans;
    ans = 1;
    for (i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
            ans = std::max(ans, i);
            x /= i;
            while (x % i == 0)
                x /= i;
        }
    }
    if (x != 1)
        ans = std::max(ans, x);
    return ans;
}
int main() {
    static int x, z, i, p, ans;
    scanf("%d", &x);
    ans = x;
    sieve(x);
    p = mpf(x);
    for (i = x - p + 1; i <= x; ++i) {
        if (!np[i])
            continue;
        z = mpf(i);
        if (i == z)
            continue;
        ans = std::min(ans, i - z + 1);
    }
    printf("%d\n", ans);

    return 0;
}
