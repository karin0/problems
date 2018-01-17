#include <cstdio>
#include <cmath>
#include <algorithm>

const int MAXN = 200005;
int n;
struct Vec {
    int x, y;
} ps[MAXN];
double dist(const Vec &a, const Vec &b) {
    int dx = a.x - b.x, dy = a.y - b.y;
    return sqrt((long long)dx * dx + (long long)dy * dy);
}
bool cmp_x(const Vec &a, const Vec &b) {
    return a.x < b.x;
}
bool cmp_y(const Vec &a, const Vec &b) {
    return a.y < b.y;
}
double solve(Vec *l, Vec *r) {
    static Vec t[MAXN];
    if (r - l == 2)
        return dist(*l, *(l + 1)) + dist(*l, *(r - 1)) + dist(*r, *(r - 1));
    else if (r - l < 2)
        return 0x7f7f7f7f;
    Vec *mid = l + ((r - l) >> 1), *i, *p = t, *j, *k;
    double d = std::min(solve(l, mid), solve(mid + 1, r));
    double hd = d / 2, dis;
    int midx = mid->x;
    for (i = l; i < mid; ++i)
        if (midx - i->x <= hd)
            *(p++) = *i;
    for (i = mid; i <= r; ++i)
        if (i->x - midx <= hd)
            *(p++) = *i;
    std::sort(t, p, cmp_y);
    for (i = t; i < p - 2; ++i) {
        for (j = i + 1; j < p - 1; ++j) {
            if (j->y - i->y >= hd)
                break;
            dis = dist(*i, *j);
            for (k = j + 1; k < p; ++k) {
                if (k->y - i->y >= hd)
                    break;
                d = std::min(d, dis + dist(*i, *k) + dist(*j, *k));
                hd = d / 2;
            }
        }
    }
    return d;
}


int main() {
    int i;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i)
        scanf("%d%d", &ps[i].x, &ps[i].y);
    std::sort(ps + 1, ps + n + 1, cmp_x);
    printf("%.6f\n", solve(ps + 1, ps + n));

    return 0;
}
