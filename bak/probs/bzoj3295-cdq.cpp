#include <cstdio>
#include <cctype>
#include <algorithm>

typedef long long ll;
const int MAXN = 100003, MAXM = 50003;
struct Query {
    int i, v, tim;
    ll *ans;
} a[MAXN];
bool operator < (const Query &p, const Query &q) {
    return p.tim < q.tim;
}
int cnt, n;
void query(int i, int v, ll *ans) {
    Query &q = a[++cnt];
    q.i = i, q.v = v, q.tim = cnt, q.ans = ans;
}
struct BIT {
    ll c[MAXN];
    inline int lowbit(int x) {
        return x & -x;
    }
    ll query(int i) {
        static ll res;
        for (res = 0; i >= 1; i -= lowbit(i))
            res += c[i];
        return res;
    }
    void update(int i, int x) {
        for (; i <= n; i += lowbit(i))
            c[i] += x;
    }
    void clear(int i) {
        for (; i <= n && c[i]; i += lowbit(i))
            c[i] = 0;
    }
} bit;
void cdq(Query *l, Query *r) {
    static Query t[MAXN];
    if (l == r)
        return;
    Query *mid = l + (r - l) / 2;
    cdq(l, mid);
    cdq(mid + 1, r);
    for (Query *q = t, *p1 = l, *p2 = mid + 1; q <= t + (r - l); ++q) {
        if ((p1 <= mid && p1->i <= p2->i) || p2 > r) {
            *q = *(p1++);
            bit.update(q->v, 1);
        } else {
            *q = *(p2++);
            *(q->ans) += bit.query(q->v);
        }
    }
    for (Query *q = t, *p = l; p <= r; ++p, ++q) {
        *p = *q;
        bit.clear(q->v);
    }
}
void read(int &x) {
    static char c;
    for (c = 0; !isdigit(c); c = getchar());
    for (x = 0; isdigit(c); c = getchar())
        x = x * 10 + (c - '0');
}
int main() {
    static int m, val[MAXN], ind[MAXN], del[MAXM], removed[MAXN], x, i;
    static ll ans[MAXM];
    read(n), read(m);
    for (i = 1; i <= n; ++i) {
        read(x);
        val[i] = x, ind[x] = i;
    }
    for (i = 1; i <= m; ++i) {
        read(x);
        del[i] = ind[x], removed[ind[x]] = true;
    }
    for (i = 1; i <= n; ++i)
        if (!removed[i])
            query(i, val[i], ans + m + 1);
    for (i = m; i >= 1; --i)
        query(del[i], val[del[i]], ans + i);
    for (i = 1; i <= cnt; ++i)
        a[i].i = n - a[i].i + 1;
    cdq(a + 1, a + cnt);
    std::sort(a + 1, a + cnt + 1);
    for (i = 1; i <= cnt; ++i) {
        a[i].v = n - a[i].v + 1;
        a[i].i = n - a[i].i + 1;
    }
    cdq(a + 1, a + cnt);
    for (i = m; i >= 1; --i)
        ans[i] += ans[i + 1];
    for (i = 1; i <= m; ++i)
        printf("%lld\n", ans[i]);

    return 0;
}
