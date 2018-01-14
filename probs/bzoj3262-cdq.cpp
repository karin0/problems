#include <cstdio>
#include <algorithm>
 
const int MAXN = 100005, MAXM = 200005;
int n, m, cnt;
struct Item {
    int x, y, z, sum, ans;
} *q[MAXN], qwq[MAXN];
bool operator < (const Item &a, const Item &b) {
    return (a.x < b.x) || 
        (a.x == b.x && a.y < b.y) || 
        (a.x == b.x && a.y == b.y && a.z < b.z);
}
bool cmp(const Item *a, const Item *b) {
    return (a->y < b->y) || (a->y == b->y && a->x < b->x);
}
struct BIT {
    int c[MAXM << 2];
    inline int lowbit(int x) {
        return x & -x;
    }
    void add(int i, int x) {
        for (; i <= m; i += lowbit(i))
            c[i] += x;
    }
    int query(int i) {
        static int res, o;
        for (res = 0, o = i; o >= 1; o -= lowbit(o))
            res += c[o]; // c[o] instead of c[i]
        return res;
    }
} bit;
void cdq(int l, int r) {
    if (l == r)
        return;
    static Item *t[MAXN];
    int mid = (l + r) >> 1, i;
    for (i = l; i <= r; ++i)
        if (q[i]->x <= mid)
            bit.add(q[i]->z, q[i]->sum);
        else
            q[i]->ans += bit.query(q[i]->z);
    for (i = l; i <= r; ++i)
        if (q[i]->x <= mid)
            bit.add(q[i]->z, -q[i]->sum);
    int c1 = l - 1, c2 = mid;
    for (i = l; i <= r; ++i)
        if (q[i]->x <= mid)
            t[++c1] = q[i];
        else
            t[++c2] = q[i];
    for (i = l; i <= r; ++i)
        q[i] = t[i];
    cdq(l, mid);
    cdq(mid + 1, r);
}
int main() {
    static int i, ans[MAXN];
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i) {
        scanf("%d%d%d", &qwq[i].x, &qwq[i].y, &qwq[i].z);
        qwq[i].sum = 1;
    }
    std::sort(qwq + 1, qwq + n + 1);
    q[++cnt] = qwq + 1;
    for (i = 2; i <= n; ++i)
        if (qwq[i - 1] < qwq[i])
            q[++cnt] = qwq + i;
        else
            ++q[cnt]->sum;
    for (i = 1; i <= cnt; ++i)
        q[i]->x = i, q[i]->ans += q[i]->sum - 1;
    std::sort(q + 1, q + cnt + 1, cmp);
    cdq(1, cnt);
    for (i = 1; i <= cnt; ++i)
        ans[q[i]->ans] += q[i]->sum;
    for (i = 0; i < n; ++i)
        printf("%d\n", ans[i]);
    return 0;
}
