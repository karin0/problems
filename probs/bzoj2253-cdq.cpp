#include <cstdio>
#include <algorithm>

typedef long long ll;
const int MAXN = 50004;
struct Box {
    int x, y, z, f;
} a[MAXN];
bool cmp_x(const Box &p, const Box &q) {
    return p.x < q.x;
}
bool cmp_y(const Box &p, const Box &q) {
    return p.y < q.y;
}
int zmax, ans = 1;
struct BIT {
    int c[MAXN];
    inline int lowbit(int x) {
        return x & -x;
    }
    int query(int i) {
        static int res;
        for (res = 0; i >= 1; i -= lowbit(i))
            res = std::max(res, c[i]);
        return res;
    }
    void update(int i, int x) {
        for (; i <= zmax; i += lowbit(i))
            c[i] = std::max(c[i], x);
    }
    void clear(int i) {
        for (; i <= zmax && c[i]; i += lowbit(i))
            c[i] = 0;
    }
} bit;
void cdq(Box *l, Box *r) {
    if (l == r)
        return;
    Box *mid = l + (r - l) / 2;
    while (mid < r && mid->x == (mid + 1)->x)
        ++mid;
    if (mid == r) {
        mid = l + (r - l) / 2;
        while (mid > l && mid->x == (mid - 1)->x)
            --mid;
        if (mid == l)
            return;
    }
    cdq(l, mid);
    std::sort(l, mid + 1, cmp_y);
    std::sort(mid + 1, r + 1, cmp_y);
    for (Box *p1 = l, *p2 = mid + 1; p1 <= mid || p2 <= r; ) {
        if ((p1 <= mid && p1->y <= p2->y) || p2 > r) {
            bit.update(p1->z, p1->f + 1);
            ++p1;
        } else {
            p2->f = std::max(p2->f, bit.query(p2->z - 1));
            ans = std::max(ans, p2->f);
            ++p2;
        }
    }
    for (Box *q = l; q <= mid; ++q)
        bit.clear(q->z);
    std::sort(mid, r + 1, cmp_x);
    cdq(mid + 1, r);
}
// f[i] = max_{j < i} (f[j] + [ a[j] < a[i] ])
int main() {
    static int n, i, b, mo, la = 1, vec[4], t[MAXN], *r;
    scanf("%d%d%d", &b, &mo, &n);
    for (i = 1; i <= n; ++i) {
        vec[0] = la = ((ll)la * b) % mo;
        vec[1] = la = ((ll)la * b) % mo;
        vec[2] = la = ((ll)la * b) % mo;
        std::sort(vec, vec + 3);
        a[i].x = vec[0], a[i].y = vec[1], a[i].z = vec[2], a[i].f = 1;
        t[i] = a[i].z;
        // printf("%d is (%d, %d, %d)\n", i, vec[0], vec[1], vec[2]);
    }
    std::sort(t + 1, t + n + 1);
    r = std::unique(t + 1, t + n + 1);
    // zmax = r - t;
    zmax = n + 1;
    for (i = 1; i <= n; ++i)
        a[i].z = std::lower_bound(t + 1, r, a[i].z) - t + 1;
    std::sort(a + 1, a + n + 1, cmp_x);
    cdq(a + 1, a + n);
    printf("%d\n", ans);

    return 0;
}
