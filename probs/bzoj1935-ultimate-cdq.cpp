#include <cstdio>
#include <cctype>
#include <algorithm>

const int MAXN = 500002, MAXY = 10000004;
struct Query {
    int x, y, k, *ans;
} a[MAXN * 5];
int cnt, ymax;
void query(int x, int y, int k, int *ans) {
    Query &q = a[++cnt];
    q.x = x, q.y = y, q.k = k, q.ans = ans;
}
struct BIT {
    int c[MAXY];
    inline int lowbit(int x) {
        return x & -x;
    }
    int query(int i) {
        static int res;
        for (res = 0; i >= 1; i -= lowbit(i))
            res += c[i];
        return res;
    }
    void update(int i, int x) {
        for (; i <= ymax; i += lowbit(i))
            c[i] += x;
    }
    void clear(int i) {
        for (; i <= ymax && c[i]; i += lowbit(i))
            c[i] = 0;
    }
} bit;
void cdq(Query *l, Query *r) {
    static Query t[MAXN * 5];
    if (l == r)
        return;
    Query *mid = l + (r - l) / 2;
    cdq(l, mid);
    cdq(mid + 1, r);
    for (Query *q = t, *p1 = l, *p2 = mid + 1; q <= t + (r - l); ++q) {
        if ((p1 <= mid && p1->x <= p2->x) || p2 > r) {
            *q = *(p1++);
            if (!q->ans)
                bit.update(q->y, 1);
        } else {
            *q = *(p2++);
            if (q->ans)
                *(q->ans) += bit.query(q->y) * q->k;
        }
    }
    for (Query *q = t, *p = l; p <= r; ++p, ++q) {
        *p = *q;
        if (!q->ans)
            bit.clear(q->y);
    }
}
void read(int &x) {
    static char c;
    for (c = 0; !isdigit(c); c = getchar());
    for (x = 0; isdigit(c); c = getchar())
        x = x * 10 + (c - '0');
}
int main() {
    static int n, m, ans[MAXN], i, x1, y1, x2, y2;
    read(n), read(m);
    for (i = 1; i <= n; ++i) {
        read(x1), read(y1);
        x1 += 2, y1 += 2;
        ymax = std::max(ymax, y1);
        query(x1, y1, 0, NULL);
    }
    for (i = 1; i <= m; ++i) {
        read(x1), read(y1), read(x2), read(y2);
        x1 += 2, y1 += 2, x2 += 2, y2 += 2;
        ymax = std::max(ymax, std::max(y1, y2));
        query(x2, y2, 1, ans + i);
        query(x1 - 1, y2, -1, ans + i);
        query(x2, y1 - 1, -1, ans + i);
        query(x1 - 1, y1 - 1, 1, ans + i);
    }
    cdq(a + 1, a + cnt);
    for (i = 1; i <= m; ++i)
        printf("%d\n", ans[i]);

    return 0;
}
