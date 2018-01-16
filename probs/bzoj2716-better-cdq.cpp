#include <cstdio>
#include <cctype>
#include <algorithm>

const int MAXN = 500004 << 1, MAXY = 1000005;
int xmax, ymax;
struct Query {
    int x, y, tim, *ans;
    Query() {}
    Query(int _x, int _y, int _ti, int *_a) : x(_x), y(_y), tim(_ti), ans(_a) {}
} q[MAXN];
bool cmp(const Query a, const Query b) {
    return a.tim < b.tim;
}
struct BIT {
    int c[MAXY];
    inline int lowbit(int x) {
        return x & -x;
    }
    void update(int i, int x) {
        for (; i <= ymax; i += lowbit(i))
            c[i] = std::max(c[i], x);
    }
    void clear(int i) {
        for (; i <= ymax && c[i]; i += lowbit(i))
            c[i] = 0;
    }
    int query(int i) {
        static int res;
        for (res = 0; i >= 1; i -= lowbit(i))
            res = std::max(res, c[i]);
        return res;
    }
} bit;
void cdq(Query *l, Query *r) {
    static Query t[MAXN];
    if (l == r)
        return;
    Query *mid = l + ((r - l) >> 1);
    cdq(l, mid);
    cdq(mid + 1, r);
    int res;
    for (Query *p1 = l, *p2 = mid + 1, *i = t; i <= t + (r - l); ++i)
        if ((p1 <= mid && p1->x <= p2->x) || p2 > r) {
            *i = *(p1++);
            if (!i->ans)
                bit.update(i->y, i->x + i->y);
        } else {
            *i = *(p2++);
            if (i->ans && (res = bit.query(i->y))) // ***
                *(i->ans) = std::min(*(i->ans), i->x + i->y - res);
        }
    for (Query *i = t, *j = l; j <= r; ++i, ++j) {
        *j = *i;
        bit.clear(i->y);
    }
}
void read(int &x) {
    static char c;
    for (c = 0; !isdigit(c); c = getchar());
    for (x = 0; isdigit(c); c = getchar())
        x = x * 10 + (c - '0');
}
int main() {
    static int n, m, i, ans[MAXN], opt, x, y, qcnt;
    scanf("%d%d", &n, &m); // initalized 0
    for (i = 1; i <= n; ++i) {
        scanf("%d%d", &x, &y);
        x += 2, y += 2;
        xmax = std::max(xmax, x), ymax = std::max(ymax, y);
        q[i] = Query(x, y, i, NULL);
    }
    for (i = 1; i <= m; ++i) {
        scanf("%d%d%d", &opt, &x, &y);
        x += 2, y += 2;
        xmax = std::max(xmax, x), ymax = std::max(ymax, y);
        if (opt == 1)
            q[n + i] = Query(x, y, n + i, NULL);
        else
            q[n + i] = Query(x, y, n + i, ans + (++qcnt));
    }
    std::fill(ans + 1, ans + qcnt + 1, 0x7f7f7f7f);
    n += m;
    // std::sort(q + 1, q + n + 1, cmp);
    cdq(q + 1, q + n);
    for (i = 1; i <= n; ++i)
        q[i].x = xmax - q[i].x + 1;
    std::sort(q + 1, q + n + 1, cmp);
    cdq(q + 1, q + n);
    for (i = 1; i <= n; ++i)
        q[i].y = ymax - q[i].y + 1;
    std::sort(q + 1, q + n + 1, cmp);
    cdq(q + 1, q + n);
    for (i = 1; i <= n; ++i)
        q[i].x = xmax - q[i].x + 1;
    std::sort(q + 1, q + n + 1, cmp);
    cdq(q + 1, q + n);
    for (i = 1; i <= qcnt; ++i)
        printf("%d\n", ans[i]);
    return 0;
}
