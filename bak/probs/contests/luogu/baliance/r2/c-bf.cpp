#include <cstdio>
#include <algorithm>

typedef long long ll;
const int MAXN = 100005;
int n;
struct Item {
    int v, x;
} s[MAXN];
inline bool operator < (const Item &x, const Item &y) {
    return x.v > y.v;
}
ll solve(ll w) {
    static int i;
    static ll res, cost, cnt;
    res = 0;
    for (i = 1; i <= n; ++i) {
        cost = (ll)s[i].v * s[i].x;
        if (cost < w)
            w -= cost, res += s[i].x;
        else if (cost == w)
            return res + s[i].x;
        else
            cnt = w / s[i].v, res += cnt, w -= cnt * s[i].v;
    }
    return res;
}

int main() {
    static int m, i;
    static ll w;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i)
        scanf("%d%d", &s[i].v, &s[i].x);
    std::sort(s + 1, s + n + 1);
    for (i = 1; i <= m; ++i)
        scanf("%lld", &w), printf("%lld\n", solve(w));

    return 0;
}
