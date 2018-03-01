#include <cstdio>
#include <cmath>
#include <algorithm>

const int N = 10005, V = 1000003;
int n, s, a[N], cnt[V], l, r, ret[N], t, ans;
struct Query {
    int l, r, t, *ret;

    bool operator < (const Query &rhs) const {
        int a1 = l / s, a2 = rhs.l / s, b1 = r / s, b2 = rhs.r / s;
        return (a1 < a2) || (a1 == a2 && b1 < b2) || (a1 == a2 && b1 == b2 && t < rhs.t);
    }
} qwq[N];
struct Mod {
    int i, x, old;

    void act() {
        old = a[i];
        a[i] = x;
        if (l <= i && i <= r)
            ans -= bool(cnt[old]) + bool(cnt[x]), ans += bool(--cnt[old]) + bool(++cnt[x]);
    }
    void undo() const {
        a[i] = old;
        if (l <= i && i <= r)
            ans -= bool(cnt[old]) + bool(cnt[x]), ans += bool(++cnt[old]) + bool(--cnt[x]);
    }
} qmq[N];
int main() {
    static int m, cm, qm, i;
    static char opt[3];
    scanf("%d%d", &n, &m);
    s = floor(pow(n, 2.0 / 3.0) + 0.5);
    for (i = 0; i < n; ++i)
        scanf("%d", &a[i]);
    for (i = 0; i < m; ++i) {
        scanf("%s%d%d", opt, &l, &r);
        if (opt[0] == 'Q') {
            Query &q = qwq[qm];
            q.l = l - 1, q.r = r - 1, q.t = cm, q.ret = &ret[qm++];
        } else {
            Mod &q = qmq[cm++];
            q.i = l - 1, q.x = r;
        }
    }
    std::sort(qwq, qwq + qm);
    const Query &q = qwq[0];
    l = q.l, r = q.r, t = q.t;
    for (i = l; i <= r; ++i)
        ans -= bool(cnt[a[i]]), ans += bool(++cnt[a[i]]);
    for (i = 0; i < t; ++i)
        qmq[i].act();
    *q.ret = ans;
    for (i = 1; i < qm; ++i) { 
        const Query &q = qwq[i];
        while (q.l < l)
            --l, ans -= bool(cnt[a[l]]), ans += bool(++cnt[a[l]]);
        while (r < q.r)
            ++r, ans -= bool(cnt[a[r]]), ans += bool(++cnt[a[r]]);
        while (l < q.l)
            ans -= bool(cnt[a[l]]), ans += bool(--cnt[a[l]]), ++l;
        while (q.r < r)
            ans -= bool(cnt[a[r]]), ans += bool(--cnt[a[r]]), --r;
        while (t < q.t)
            qmq[t++].act();
        while (q.t < t)
            qmq[--t].undo();
        *q.ret = ans;
    }
    for (i = 0; i < qm; ++i)
        printf("%d\n", ret[i]);

    return 0;
}
