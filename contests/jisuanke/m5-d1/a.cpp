#include <cstdio>
#include <cctype>
#include <algorithm>

typedef long long ll;

ll f(ll x) {
    static ll res;
    res = x;
    while (x)
        res += x % 10, x /= 10;
    return res;
}

ll solve(ll x) {
    static ll i;
    for (i = std::max(1ll, x - 200); i < x; ++i)
        if (f(i) == x) {
            return i;
        }
    return -1;
}
void read(ll &x) {
    static char ch;
    x = 0;
    ch = 0;
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch)) {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
}
int main() {
    static int t, i;
    static ll x, ret;
    scanf("%d", &t);
    for (i = 1; i <= t; ++i) {
        scanf("%lld", &x);
        if (x == 0) {
            puts("0");
            continue;
        }
        ret = solve(x);
        if (ret == -1)
            puts("Stupid SiriusRen");
        else
            printf("%lld\n", ret);
    }
    return 0;
}
