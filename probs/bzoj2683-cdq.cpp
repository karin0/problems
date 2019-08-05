#include <cstdio>
#include <algorithm>

const int MAXN = 500003, MAXM = 200003;
int n, cnt;
struct Query {
    int x, y, d, tim, *ans;
    Query() {}
    Query(int _x, int _y, int _d, int _ti, int *_a) : x(_x), y(_y), d(_d), tim(_ti), ans(_a) {}
} q[MAXM * 5];
bool cmp(const Query a, const Query b) {
    return (a.x < b.x) || (a.x == b.x && a.tim < b.tim);
}
struct BIT {
    int c[MAXN];
    inline int lowbit(int x) {
        return x & -x;
    }
    void add(int i, int x) {
        for (; i <= n; i += lowbit(i))
            c[i] += x;
    }
    int query(int i) {
        static int res;
        for (res = 0; i >= 1; i -= lowbit(i))
            res += c[i];
        return res;
    }
} bit;
void cdq(int l, int r) {
    if (l == r)
        return;
    int mid = (l + r) >> 1, i;
    static Query t[MAXM * 5];
    for (i = l; i <= r; ++i)
        if (q[i].tim <= mid && !q[i].ans)
            bit.add(q[i].y, q[i].d);
        else if (q[i].tim > mid && q[i].ans)
            *q[i].ans += bit.query(q[i].y) * q[i].d;
    for (i = l; i <= r; ++i)
        if (q[i].tim <= mid && !q[i].ans)
            bit.add(q[i].y, -q[i].d);
    int c1 = l - 1, c2 = mid;
    for (i = l; i <= r; ++i) {
        if (q[i].tim <= mid)
            t[++c1] = q[i];
        else
            t[++c2] = q[i];
    }
    for (i = l; i <= r; ++i)
        q[i] = t[i];
    cdq(l, mid);
    cdq(mid + 1, r);
}
int main() {
    static int i, ans[MAXM], opt, x1, y1, x2, y2, d, *p, qcnt;
    scanf("%d", &n); // initalized 0
    for (i = 1; ;++i) {
        scanf("%d", &opt);
        if (opt == 3)
            break;
        if (opt == 1) {
            scanf("%d%d%d", &x1, &y1, &d);
            ++cnt; q[cnt] = Query(x1, y1, d, cnt, NULL);
        } else {
            p = ans + (++qcnt);
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            ++cnt; q[cnt] = Query(x1 - 1, y1 - 1, 1, cnt, p);
            ++cnt; q[cnt] = Query(x1 - 1, y2, -1, cnt, p);
            ++cnt; q[cnt] = Query(x2, y1 - 1, -1, cnt, p);
            ++cnt; q[cnt] = Query(x2, y2, 1, cnt, p);
        }
    }
    std::sort(q + 1, q + cnt + 1, cmp);
    cdq(1, cnt);
    for (i = 1; i <= qcnt; ++i)
        printf("%d\n", ans[i]);
    return 0;
}

