#include <cstdio>
#include <cassert>
#include <algorithm>

typedef long long ll;
const int MAXN = 100005;
int n;
struct Item {
    int v, x;
    ll c;
} s[MAXN];
ll sc[MAXN], sx[MAXN];
inline bool qaq(const Item &x, const Item &y) {
    return x.v > y.v;
}
ll solve(ll w) {
    static int i, l, r, x;
    static ll res, cost, cnt, sum;
    res = 0;
    for (i = 1; i <= n; ) {
        if (w == 0)
            return res;
        cost = s[i].c;
        if (cost < w) {
            l = i, r = n + 1;  // Able to fully buy things in [i, x]
            while (r - l > 1) {
                x = (l + r) >> 1;
                sum = sc[x] - sc[i - 1];
                if (sum == w) {
                    l = x;
                    break;
                } else if (sum < w)
                    l = x;
                else
                    r = x;
            }
            res += sx[l] - sx[i - 1];
            w -= sc[l] - sc[i - 1];
            i = l + 1;
        }
        else if (cost == w)
            return res + s[i].x;
        else
            cnt = w / s[i].v, res += cnt, w -= cnt * s[i].v, ++i;
    }
    return res;
}

int main() {
    static int m, i;
    static ll w;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i)
        scanf("%d%d", &s[i].v, &s[i].x), s[i].c = (ll)s[i].v * s[i].x;
    std::sort(s + 1, s + n + 1, qaq);
    for (i = 1; i <= n; ++i) {
        sc[i] = sc[i - 1] + s[i].c;
        sx[i] = sx[i - 1] + s[i].x;
    }
    for (i = 1; i <= m; ++i)
        scanf("%lld", &w), printf("%lld\n", solve(w));

    return 0;
}
