#include <cstdio>
#include <algorithm>

typedef unsigned long long ll;
const int MAXN = 30005, MAXL = 205;
const ll BASE = 149, BASE2 = 137;

int n, l, sig, ans;
ll x[MAXN];

char s[MAXL];
ll ha[MAXN][MAXL], ha2[MAXN][MAXL];

int main() {
    int i, j, cnt;
    scanf("%d%d%d", &n, &l, &sig);
    for (i = 1; i <= n; ++i) {
        scanf("%s", s + 1);
        for (j = 1; j <= l; ++j) {
            ha[i][j] = (ha[i][j - 1] * BASE + s[j]);// % MOD;
        }
        for (j = l; j >= 1; --j) {
            ha2[i][j] = (ha2[i][j + 1] * BASE2 + s[j]);// % MOD;
        }
    }
    for (j = 1; j <= l; ++j) {
        for (i = 1; i <= n; ++i)
            x[i] = ha[i][j - 1] * 233 + ha2[i][j + 1] * 213;
        std::sort(x + 1, x + n + 1);
        cnt = 1;
        for (i = 2; i <= n; ++i) {
            if (x[i] == x[i - 1])
                ans += cnt, ++cnt;
            else
                cnt = 1;
        }
    }

    printf("%d\n", ans);
}
