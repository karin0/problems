#include <cstdio>
#include <cctype>
#include <algorithm>

const int MAXN = 10000005;
typedef long long ll;
int n;
ll m, a[MAXN], ans;
inline void read(ll &x) {
    x = 0;
    char ch = getchar();
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
        x = x * 10 + ch - '0', ch = getchar();
}

int main() {
    static int i, j, ub;
    static ll seed;
    scanf("%d%lld", &n, &m);
    for (i = 1; i <= n; i += 100) {
        read(seed);
        a[i] = seed;
        ub = i + 99;
        for (j = i + 1; j <= ub; ++j)
            a[j] = (a[j - 1] * 109 + 107) % m;
    }
    // n = 5, a[1] = 1, a[2] = 1, a[3] = 2, a[4] = 2, a[5] = 3;
    std::sort(a + 1, a + n + 1);
    ans = a[1] + 1;
    for (i = 2; i <= n; ++i) {
        // printf("a[%d] = %lld\n", i, a[i]);
        if (a[i] != a[i - 1])
            ans += a[i] + 1;
    }
    printf("%lld\n", ans);

    return 0;
}
