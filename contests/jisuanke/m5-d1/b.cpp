#include <cstdio>
#include <math.h>
#include <algorithm>

typedef long long ll;
const int MAXN = 100005;
int n, sp = 1, ans = 1;
ll a[MAXN];

ll gcd(ll x, ll y) {
    return y ? gcd(y, x % y) : x;
}

int main() {
    static int i, k, l, ml;
    static ll g, pr, q, ma, *b;
    static bool flag;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%lld", a + i);
        ma = std::max(ma, a[i]);
    }
    for (i = 2; i <= n; ++i) {
        if (a[i] == a[i - 1])
            sp += 1, ans = std::max(ans, sp);
        else
            sp = 1;
    }
    if (ans == n) {
        printf("%d\n", n);
        return 0;
    }
    ml = ceil(log2(ma));
    for (i = 1; i < n; ++i) {
        for (l = ans + 1; l <= ml; ++l) {
            b = a + i - 1;
            if (i + l - 1 > n)
                break;
            g = b[1];
            for (k = 2; k <= l; ++k)
                g = gcd(g, b[k]);
            for (k = 1; k <= l; ++k)
                b[k] /= g;
            std::sort(b + 1, b + l + 1);
            if (b[2] % b[1])
                continue;
            q = b[2] / b[1];
            flag = false;
            for (k = 3; k <= l; ++k) {
                if (b[k] % b[k - 1]) {
                    flag = true;
                    break;
                }
                q = gcd(q, b[k] / b[k - 1]);
                if (q == 1) {
                    flag = true;
                    break;
                }
            }
            if (flag || q > 1000)
                continue;
            pr = b[1];
            for (k = 2; k <= l; ++k) {
                while (pr < b[k])
                    pr *= q;
                if (pr > b[k] || pr < 0) {
                    flag = true;
                    break;
                }
            }
            if (flag)
                continue;
            ans = std::max(ans, l);
        }
    }
    printf("%d\n", ans);
    return 0;
}
