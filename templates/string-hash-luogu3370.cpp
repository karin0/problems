#include <cstdio>
#include <algorithm>

typedef long long ll;
const int MAXN = 10005, MAXS = 1505;
const int MOD = 998244353, BASE = 131;
int n, arr[MAXN];
char s[MAXS];
int main() {
    static int i;
    static char *c;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%s", s);
        int &ha = arr[i];
        for (c = &s[0]; *c; ++c)
            ha = ((ll)ha * BASE + *c) % MOD; // ll!
    }
    std::sort(arr + 1, arr + n + 1);
    printf("%d\n", (int)(std::unique(arr + 1, arr + n + 1) - arr) - 1);

    return 0;
}
