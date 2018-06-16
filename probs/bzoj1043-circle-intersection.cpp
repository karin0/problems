#include <bits/stdc++.h>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))
#ifdef AKARI
    #define ccc(x) std::cerr << #x " = " << (x) << "  "
    #define ccf(x) std::cerr << #x " = " << (x) << std::endl
    #define cccc(...) fprintf(stderr, __VA_ARGS__)
#else
    #define ccc(x)
    #define ccf(x)
    #define cccc(...)
#endif
typedef long long ll;
const int N = 1007;
const double pi = acos(-1), eps = 1e-8;

int dcmp(const double x) {
    return fabs(x) <= eps ? 0 : (x > 0 ? 1 : -1);
}
int dcmp(const double x, const double y) {
    return dcmp(x - y);
}
struct point_t {
    double x, y;
    point_t() {}
    point_t(const double _x, const double _y) : x(_x), y(_y) {}
    point_t(const point_t &p, const point_t &q) : x(q.x - p.x), y(q.y - p.y) {}
    double norm() const {
        return x * x + y * y;
    }
    double polar() const {
        return atan2(y, x);
    }
};
struct circle_t {
    point_t p;
    double r, rr;
} cir[N];
struct range_t {
    double l, r;
    range_t() {}
    range_t(const double _l, const double _r) : l(_l), r(_r) {}
    bool operator < (const range_t &rh) const {
        return l < rh.l;
    }
} ran[N * 2];
int rcnt;
void add(const double l, const double r) {
    ran[++rcnt] = range_t(l, r);
}
void intersect(const circle_t &c1, const circle_t &c2) {
    point_t v = point_t(c1.p, c2.p);
    double dd = v.norm(), d = sqrt(dd);
    if (dcmp(d, c1.r + c2.r) >= 0)
        return;
    if (dcmp(d, c1.r - c2.r) <= 0)
        return;
    if (dcmp(d, c2.r - c1.r) <= 0)
        return add(-pi, pi);
    double a = acos((dd + c1.rr - c2.rr) / (2 * c1.r * d)), k = v.polar();
    double l = k - a, r = k + a;
    if (dcmp(l, -pi) < 0)
        add(l + 2 * pi, pi), add(-pi, r);
    else if (dcmp(r, pi) >= 0)
        add(l, pi), add(-pi, r - 2 * pi);
    else
        add(l, r);
}
int main() {
    static int n, i, j;
    static double ans, l, t;
    scanf("%d", &n);
    rep (i, 1, n) {
        circle_t &q = cir[i];
        scanf("%lf%lf%lf", &q.r, &q.p.x, &q.p.y);
        q.rr = q.r * q.r;
    }
    rep (i, 1, n) {
        rcnt = 0;
        rep (j, i + 1, n)
            intersect(cir[i], cir[j]);
        std::sort(ran + 1, ran + rcnt + 1);
        l = -pi;
        t = 2 * pi;
        rep (j, 1, rcnt) { // **
            const range_t &q = ran[j];
            t -= std::max((double)0, q.r - std::max(l, q.l));
            l = std::max(l, q.r);
        }
        ans += cir[i].r * t;
    }
    printf("%.3f\n", ans);

    return 0;
}

