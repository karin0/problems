#include <cstdio>
#include <cstring>
#include <algorithm>

typedef long long ll;
const ll MIN = 10000000000;
ll f[11][11][10][2][2][2][2];
int a[11], pow2[];
ll dp(int w, int lim, int last, bool eqn, bool tri, bool q4, bool q8) {
    ll &ans = f[w][lim][last][eqn][tri][q4][q8];
    if (ans != -1)
        return ans;
    ans = 0;
    int i;
    if (w == 0) { // 枚举 10^0 位（个位）之数字
        for (i = 0; i <= std::min(lim, 9); ++i) {
            if (i == 4 && q8)
                continue;
            if (i == 8 && q4)
                continue;
            if (tri || (eqn && last == i))
                ++ans;
        }
    } else {
        for (i = 0; i <= std::min(lim, 9); ++i) {
            if (i == 4 && q8)
                continue;
            if (i == 8 && q4)
                continue;
            ans += dp(w - 1, (i < lim || lim == 10) ? 10 : a[w - 1], i, i == last, tri || (eqn && i == last), q4 || (i == 4), q8 || (i == 8));
        }
    }
    return ans;
}
ll calc(ll x) {
    static int i;
    static ll res;
    if (x < MIN)
        return 0;
    for (i = 0; i <= 10; ++i)
        a[i] = x % 10, x /= 10;
    memset(f, -1, sizeof(f));
    res = 0;
    for (i = 1; i <= a[10]; ++i) // 枚举 10^10 位之数字（不可为 0）
        res += dp(9, (i < a[10]) ? 10 : a[9], i, false, false, i == 4, i == 8);
    return res;
}

int main() {
    static ll l, r;
    scanf("%lld%lld", &l, &r);
    printf("%lld\n", calc(r) - calc(l - 1));

    return 0;
}
