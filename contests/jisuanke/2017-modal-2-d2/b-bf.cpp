#include <cstdio>
#include <cmath>

typedef long long ll;
const int MAXN = 100005;
const double EPS = 1e-6;

struct Point {
    double x, y;
};
struct Line {
    ll k, b;
};
inline Point cap(const Line &a, const Line &b) {
    double y = (double)(a.b * b.k - b.b * a.k) / (b.k - a.k);
    return Point{(y - a.b) / a.k, y};
}
inline double dist(const Point &p, const Line &l) {
    return fabs(l.k * p.x - p.y + l.b) / sqrt(l.k * l.k + 1);
}

int n;
Line sl[MAXN];
ll ans;

int main() {
    ll k, a, b;
    int i, j;
    Line la, lb;
    Point p;
    double d;
    scanf("%lld%lld%lld%d", &k, &a, &b, &n);
    la.k = k, la.b = a, lb.k = k, lb.b = b;
    d = dist((Point){0.0, (double)la.b}, lb);
    for (i = 1; i <= n; ++i) {
        scanf("%lld%lld", &k, &b);
        sl[i].k = k, sl[i].b = b;
        for (j = 1; j < i; ++j) {
            p = cap(sl[j], sl[i]);
            if (fabs(dist(p, la) + dist(p, lb) - d) <= EPS)
                ++ans;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
