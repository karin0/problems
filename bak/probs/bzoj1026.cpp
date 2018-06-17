#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAXD = 20, BASE = 10;
int digit[MAXD], f[MAXD][BASE + 1][2];

inline int dfs(int pos, int prev, int zero, bool lim) {
    if (pos < 0)
        return 1;
    int &dp = f[pos][prev][zero];
    if (!lim && dp != -1)
        return dp;
    int ub = lim ? digit[pos] : BASE - 1, res = 0;
    for (int i = 0; i <= ub; ++i)
        if (!zero || std::abs(i - prev) >= 2)
            res += dfs(pos - 1, i, zero || i, lim && (i == ub));
    return lim ? res : (dp = res);
}

inline int g(int x) {
    if (x < 0)
        return 0;
    int i, t;
    for (i = 0; x; t = x, x /= 10, digit[i++] = t - x * 10);
    return dfs(i - 1, 0, 0, true);
}

int main() {
    int a, b;
    scanf("%d%d", &a, &b);

    memset(f, -1, sizeof(f));
    printf("%d\n", g(b) - g(a - 1));

    return 0;
}
