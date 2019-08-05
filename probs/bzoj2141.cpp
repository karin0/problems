#include <cstdio>
#include <algorithm>

typedef long long ll;
const int N = 100003;

int n, m, t[N], p[N];
ll a, b, c;
ll sp[N], rp[N], st[N];
int main() {
    static int i;
    static ll ans = 1ll << 62, res, x, y, tmp, l, r, cur;
    scanf("%lld%lld%lld%d%d", &a, &b, &c, &n, &m);
    for (i = 1; i <= n; ++i)
        scanf("%d", &t[i]);
    for (i = 1; i <= m; ++i)
        scanf("%d", &p[i]);
    std::sort(t + 1, t + n + 1);
    std::sort(p + 1, p + m + 1);
    t[n + 1] = N;
    for (i = 1; i <= n; ++i)
        st[i] = st[i - 1] + t[i];
    for (i = 1; i <= m; ++i)
        sp[i] = sp[i - 1] + p[i];
    for (i = m; i >= 1; --i)
        rp[i] = rp[i + 1] + p[i];
    for (i = 1; i <= p[m]; ++i) {
        cur = std::lower_bound(t + 1, t + n + 1, i) - t - 1;
        tmp = (ll)i * cur - st[cur];
        if (c >= N && tmp > 0)
            continue;
        res = tmp * c;
        l = std::lower_bound(p + 1, p + m + 1, i) - p - 1;
        r = std::upper_bound(p + 1, p + m + 1, i) - p;
        x = l * i - sp[l];
        y = rp[r] - (m - r + 1) * i;
        res += std::min(a * std::min(x, y) + b * std::max(y - x, 0ll), b * y);
        ans = std::min(ans, res);
    }
    printf("%lld\n", ans);

    return 0;
}
