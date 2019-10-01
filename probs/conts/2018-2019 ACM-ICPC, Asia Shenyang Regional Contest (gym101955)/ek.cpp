#include <algorithm>
#include <cstdio>
#include <iostream>
const int N = 100005;
typedef long long ll;
const ll INF = 1e12;
typedef std::pair<ll, int> P;
ll val[4][N], x[N], y[N];
int T, kase, n, m, blg[N];
P a[4];
const P o = P(-INF, 0);
struct Node {
    P v[2];
    Node() {
        v[0] = v[1] = o;
    }
};
Node merge(const Node& l, const Node& r) {
    Node res;
    a[0] = l.v[0];
    a[1] = l.v[1];
    a[2] = r.v[0];
    a[3] = r.v[1];
    std::sort(a, a + 4, std::greater<P>());
    res.v[0] = a[0];
    for (int i = 1; i < 4; i++)
        if (a[i].second != a[0].second) {
            res.v[1] = a[i];
            break;
        }
    return res;
}
struct SegTree {
    Node val[N << 2];
    void pull(ll k)
    {
        val[k] = merge(val[k << 1], val[k << 1 | 1]);
    }
    void build(int k, int lef, int rig, ll* v)
    {
        if (lef == rig) {
            val[k].v[0] = P(v[lef], blg[lef]);
            val[k].v[1] = o;
            return;
        }
        int mid = (lef + rig) >> 1;
        build(k << 1, lef, mid, v), build(k << 1 | 1, mid + 1, rig, v);
        pull(k);
    }
    void update(int k, int lef, int rig, int p, const P& v)
    {
        if (lef == rig) {
            val[k].v[0] = v;
            return;
        }
        int mid = (lef + rig) >> 1;
        if (p <= mid)
            update(k << 1, lef, mid, p, v);
        else
            update(k << 1 | 1, mid + 1, rig, p, v);
        pull(k);
    }
    Node query(int k, int lef, int rig, int l, int r)
    {
        if (l <= lef && rig <= r)
            return val[k];
        int mid = (lef + rig) >> 1;
        Node res;
        if (l <= mid)
            res = merge(res, query(k << 1, lef, mid, l, r));
        if (r > mid)
            res = merge(res, query(k << 1 | 1, mid + 1, rig, l, r));
        return res;
    }
} t[4];
const int f[2] = { -1, 1 };
int main()
{
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) {
            scanf("%lld%lld%d", x + i, y + i, blg + i);
            for (int j = 0; j < 2; j++)
                for (int k = 0; k < 2; k++)
                    val[j << 1 | k][i] = x[i] * f[j] + y[i] * f[k];
        }
        for (int i = 0; i < 4; i++)
            t[i].build(1, 1, n, val[i]);
        int op, l, r, k;
        printf("Case #%d:\n", ++kase);
        while (m--) {
            scanf("%d", &op);
            if (op == 1) {
                scanf("%d%d%d", &k, &l, &r);
                x[k] += l;
                y[k] += r;
                for (int i = 0; i < 2; i++)
                    for (int j = 0; j < 2; j++) {
                        val[i << 1 | j][k] = x[k] * f[i] + y[k] * f[j];
                        t[i << 1 | j].update(1, 1, n, k, P(val[i << 1 | j][k], blg[k]));
                    }
            } else if (op == 2) {
                scanf("%d%d", &l, &r);
                blg[l] = r;
                for (int i = 0; i < 4; i++)
                    t[i].update(1, 1, n, l, P(val[i][l], r));
            } else {
                ll ans = 0;
                Node L, R;
                scanf("%d%d", &l, &r);
                for (int i = 0; i < 2; i++) {
                    L = t[i].query(1, 1, n, l, r), R = t[3 - i].query(1, 1, n, l, r);
                    if (L.v[0].second != R.v[0].second)
                        ans = std::max(ans, L.v[0].first + R.v[0].first);
                    else {
                        if (R.v[1].second)
                            ans = std::max(ans, L.v[0].first + R.v[1].first);
                        if (L.v[1].second)
                            ans = std::max(ans, L.v[1].first + R.v[0].first);
                    }
                }
                printf("%lld\n", ans);
            }
        }
    }
}