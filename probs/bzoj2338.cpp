#include <cstdio>
#include <algorithm>

const int MAXN = 1505;
typedef long long ll;
struct Point {
    int x, y;
    Point (int _x = 0, int _y = 0) : x(_x), y(_y) {}
    Point operator + (const Point &b) const {
        return Point(x + b.x, y + b.y);
    }
    Point operator - (const Point &b) const {
        return Point(x - b.x, y - b.y);
    }
} ps[MAXN];
ll cross(const Point &p, const Point &q) {
    return (ll)p.x * q.y - (ll)p.y * q.x;
}
struct Segment {
    Point a, b;
    ll norm() const {
        static int dx, dy;
        dx = a.x - b.x, dy = a.y - b.y;
        return (ll)dx * dx + (ll)dy * dy;
    }
} s[MAXN * MAXN / 2];
bool scmp(const Segment &p, const Segment &q) {
    static ll np, nq;
    static Point tp, tq;
    np = p.norm(), nq = q.norm();
    if (np != nq)
        return np < nq;
    tp = p.a + p.b, tq = q.a + q.b;
    return (tp.x < tq.x) || (tp.x == tq.x && tp.y < tq.y);
}
bool has_common_midpoint(const Segment &p, const Segment &q) {
    return (p.a.x + p.b.x == q.a.x + q.b.x && p.a.y + p.b.y == q.a.y + q.b.y);
}
bool has_common_length(const Segment &p, const Segment &q) {
    return p.norm() == q.norm();
}
ll get_area_of_rectangle(const Segment &p, const Segment &q) {
    return std::abs(cross(q.a - p.a, q.b - p.a));
}


int main() {
    static int n, i, j, cnt;
    static ll ans;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i)
        scanf("%d%d", &ps[i].x, &ps[i].y);
    for (i = 1; i < n; ++i)
        for (j = i + 1; j <= n; ++j)
            s[++cnt].a = ps[i], s[cnt].b = ps[j];
    std::sort(s + 1, s + cnt + 1, scmp);
    for (i = 1; i < cnt; ++i)
        for (j = i + 1; j <= cnt && 
                has_common_midpoint(s[i], s[j]) && has_common_length(s[i], s[j])
                ; ++j)
            ans = std::max(ans, get_area_of_rectangle(s[i], s[j]));
    printf("%lld\n", ans);
    return 0;
}
