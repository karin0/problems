#include <cstdio>
#include <algorithm>

typedef long long ll;
const int N = 50005;
struct Item {
    int x, y;
} qwq[N], t[N], l[N];
bool operator < (const Item &a, const Item &b) {
    return (a.x < b.x) || (a.x == b.x && a.y < b.y);
}
int n, cnt;
ll f[N], q[N], *hd, *tl;
double slope(int i, int j) {
    return ((double)(f[i] - f[j])) / (l[i + 1].y - l[j + 1].y);
}
int main() {
    static int i;
    // freopen("acquire.in", "r", stdin);
    // freopen("acquire.out", "w", stdout);
    scanf("%d", &n);
    for (i = 1; i <= n; ++i)
        scanf("%d%d", &qwq[i].x, &qwq[i].y);
    std::sort(qwq + 1, qwq + n + 1);
    l[++cnt] = qwq[1];
    for (i = 2; i <= n; ++i) {
        while (cnt && qwq[i].y >= l[cnt].y)
            --cnt;
        l[++cnt] = qwq[i];
    }
    n = cnt;
    hd = q + 1, tl = q;
    *(++tl) = 0; // ***
    for (i = 1; i <= n; ++i) {
        // x up, y down
        // f[i] = min_{j < i} {f[j] + y[j + 1] * x[i]}
        // Considering - k < j < i
        //             - As for f[i], j is better
        // Then f[k] + y[k + 1] * x[i] > f[j] + y[j + 1] * x[i]
        //      f[k] - f[j] > x[i] * (y[j + 1] - y[k + 1])
        //     (f[k] - f[j]) / (y[k + 1] - y[j + 1]) > -x[i]
        // So for k < j < i and slope(k, j) >  -x[i], j is better
        //    for k < j < i and slope(k, j) <= -x[i], k is better
        // For k < j < i and slope(k, j) <= slope(j, i), j is useless.
        // 决策为上凸包
        while (tl - hd + 1 > 1 && slope(*hd, *(hd + 1)) > -l[i].x)
            ++hd;
        f[i] = f[*hd] + ((ll)l[(*hd) + 1].y) * l[i].x;
        while (tl - hd + 1 > 1 && slope(*(tl - 1), *tl) < slope(*tl, i))
            --tl;
        *(++tl) = i;
    }
    printf("%lld\n", f[n]);

    return 0;
}
