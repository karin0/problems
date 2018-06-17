#include <cstdio>
#include <cmath>

struct Point {
    long long x, y;
};
inline double dist(Point& a, Point& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
inline long long area2(Point& a, Point& b, Point& c) {
    double la = dist(b, c);
    double lb = dist(a, c);
    double lc = dist(a, b);
    double p = (la + lb + lc) / 2.0;
    return round(2.0 * sqrt(p * (p - la) * (p - lb) * (p - lc)));
}

int main() {
    Point v[3];
    scanf("%lld%lld%lld%lld%lld%lld", &v[0].x, &v[0].y, &v[1].x, &v[1].y, &v[2].x, &v[2].y);
    printf("%lld\n", area2(v[0], v[1], v[2]));

    return 0;
}
