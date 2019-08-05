#include <cstdio>
#include <cmath>
#include <cctype>
#include <algorithm>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))

typedef long long ll;
const int N = 2003;
struct Point {
    double x, y;
    Point(double _x = 0, double _y = 0) : x(_x), y(_y) {}
    bool operator < (const Point &rhs) const {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
    Point operator - (const Point &rhs) const {
        return Point(x - rhs.x, y - rhs.y);
    }
    double norm() const {
        return x * x + y * y;
    }
} po[N], co[N];
inline Point vec(const Point &a, const Point &b) {
    return b - a;
}
inline double cross(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}
int build_convex(int n) {
    static int m, i, k;
    std::sort(po, po + n);
    m = 0;
    re (i, 0, n) {
        while (m > 1 && cross(vec(co[m - 2], co[m - 1]), vec(co[m - 2], po[i])) <= 0) // ???
            --m;
        co[m++] = po[i];
    }
    k = m;
    per (i, n - 1, 0) {
        while (m > k && cross(vec(co[m - 2], co[m - 1]), vec(co[m - 2], po[i])) <= 0) // ???
            --m;
        co[m++] = po[i];
    }
    if (m > 1)
        --m;
    return m;
}
int m;
inline int succ(int x) {
    if (++x >= m)
        return x - m;
    return x;
}
double rc() {
    static int i, j, p, q;
    static Point s;
    static double ans, a, b, c, d;
    co[m] = co[0];
    ans = 0;
    re (i, 0, m) {
        p = succ(succ(i)), q = succ(i);
        re (j, succ(i), m) {
            s = vec(co[i], co[j]);
            a = cross(vec(co[i], co[q]), s);
            while (succ(q) != j && (b = cross(vec(co[i], co[q + 1]), s)) > a)
                q = succ(q), a = b;
            c = cross(s, vec(co[i], co[p]));
            while (succ(p) != i && (d = cross(s, vec(co[i], co[p + 1]))) > c)
                p = succ(p), c = d;
            ans = std::max(ans, a + c);
        }
    }
    return ans;
}

int main() {
    static int n, i;
    scanf("%d", &n);
    re (i, 0, n)
        scanf("%lf%lf", &po[i].x, &po[i].y);
    m = build_convex(n);
    printf("%.3lf\n", rc() / 2.0);
    return 0;
}
