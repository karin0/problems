#include <cstdio>
#include <cmath>
#include <algorithm>

const int N = 10003;
const double eps = 1e-8, tau = 2.0 * acos(-1.0);
int dcmp(double x) {
    if (fabs(x) <= eps)
        return 0;
    return x < 0 ? -1 : 1;
}
struct Vec {
    double x, y;
    Vec(double _x = 0, double _y = 0) : x(_x), y(_y) {}
    Vec operator + (const Vec &b) const {
        return Vec(x + b.x, y + b.y);
    }
    Vec operator - (const Vec &b) const {
        return Vec(x - b.x, y - b.y);
    }
    Vec rotate(const double a) const {
        static double c, s;
        c = cos(a), s = sin(a);
        return Vec(x * c - y * s, x * s + y * c);
    }
    double norm() const {
        return x * x + y * y;
    }
};
double cross(const Vec &a, const Vec &b) {
    return a.x * b.y - a.y * b.x;
}
Vec pol;
bool pcmp(const Vec &a, const Vec &b) {
    Vec pa = a - pol, pb = b - pol;
    double c = cross(pa, pb);
    if (dcmp(c))
        return c > 0;
    return pa.norm() < pb.norm();
}
struct Convex {
    Vec pts[N << 2], res[N << 2];
    int n, cnt;
    void add(const Vec &p) {
        pts[++n] = p;
    }
    void exec() {
        int k = 1, i;
        for (i = 2; i <= n; ++i)
            if (pts[i].x < pts[k].x || (dcmp(pts[i].x - pts[k].x) == 0 && pts[i].y < pts[k].y))
                    k = i;
        if (k != 1)
            std::swap(pts[k], pts[1]);
        pol = pts[1];
        std::sort(pts + 2, pts + n + 1, pcmp);
        res[++cnt] = pts[1];
        for (i = 2; i <= n; ++i) {
            while (cnt >= 2 && dcmp(cross(res[cnt] - res[cnt - 1], pts[i] - res[cnt])) <= 0)
                --cnt;
            res[++cnt] = pts[i];
        }
    }
    double get_circumference() {
        double ans = sqrt((res[1] - res[cnt]).norm());
        for (int i = 2; i <= cnt; ++i)
            ans += sqrt((res[i] - res[i - 1]).norm());
        return ans;
    }
} cx;
int main() {
    static int n, i;
    static double a, b, r, x, y, t;
    static Vec p;
    scanf("%d%lf%lf%lf", &n, &a, &b, &r);
    std::swap(a, b);
    a = a / 2 - r, b = b / 2 - r;
    for (i = 1; i <= n; ++i) {
        scanf("%lf%lf%lf", &x, &y, &t);
        p = Vec(x, y);
        cx.add(p + Vec(a, b).rotate(t));
        cx.add(p + Vec(-a, b).rotate(t));
        cx.add(p + Vec(-a, -b).rotate(t));
        cx.add(p + Vec(a, -b).rotate(t));
    }
    cx.exec();
    printf("%.2f\n", cx.get_circumference() + tau * r);

    return 0;
}
