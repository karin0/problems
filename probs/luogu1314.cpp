#include <cstdio>
#include <algorithm>

typedef long long ll;
const int MAXN = 200005;
int n, m, w[MAXN], v[MAXN], maxw;
ll s, ans = 1l << 60;
struct Query {
    int l, r;
} qwq[MAXN];

ll sv[MAXN], si[MAXN];
bool check(int x) {
    static int i, l, r;
    static ll y;
    for (i = 1; i <= n; ++i) {
        if (w[i] >= x)
            sv[i] = sv[i - 1] + v[i], si[i] = si[i - 1] + 1;
        else
            sv[i] = sv[i - 1], si[i] = si[i - 1];
    }
    y = 0;
    for (i = 1; i <= m; ++i) {
        l = qwq[i].l, r = qwq[i].r;
        y += (si[r] - si[l - 1]) * (sv[r] - sv[l - 1]);
    }
    // y 随 x 单调减
    ans = std::min(ans, std::abs(s - y));
    return y < s;
}

int main() {
    static int i, l, r, x;
    scanf("%d%d%lld", &n, &m, &s);
    for (i = 1; i <= n; ++i)
        scanf("%d%d", w + i, v + i), maxw = std::max(maxw, w[i]);
    for (i = 1; i <= m; ++i)
        scanf("%d%d", &qwq[i].l, &qwq[i].r);
    l = 0, r = maxw + 1; // [l, r]
    while (r - l > 1) {
        x = (l + r) >> 1;
        if (check(x)) // 过大
            r = x - 1;
        else // 较小
            l = x + 1;
    }
    check(l), check(r);
    printf("%lld\n", ans);

    return 0;
}
