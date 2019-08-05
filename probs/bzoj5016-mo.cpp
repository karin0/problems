#include <cstdio>
#include <cmath>
#include <algorithm>
#define rep(__i, __s, __t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i, __s, __t) for((__i)=(__s);(__i)<(__t);++(__i))
const int N = 50003;
typedef long long ll;

int s, cl[N], cr[N];
struct Query {
    int l, r;
    ll *ans;
    bool add;
    bool operator < (const Query &rhs) const {
        static int a, b;
        a = l / s, b = rhs.l / s;
        return a < b || (a == b && r < rhs.r);
    }
} qwq[N << 2];
int main() {
    static int n, m, i, l1, r1, l2, r2, a[N], p, l, r;
    static ll res[N], ans;
    scanf("%d", &n);
    s = floor(sqrt(0.8 * n) + 0.5);
    re (i, 0, n)
        scanf("%d", &a[i]);
    scanf("%d", &m);
    re (i, 0, m) {
        scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
        l1 -= 2, l2 -= 2, --r1, --r2;
        ll *ptr = &res[i];
        qwq[p++] = Query{r1, r2, ptr, true};
        if (l2 >= 0)
            qwq[p++] = Query{r1, l2, ptr, false};
        if (l1 >= 0)
            qwq[p++] = Query{l1, r2, ptr, false};
        if (l1 >= 0 && l2 >= 0)
            qwq[p++] = Query{l1, l2, ptr, true};
    }
    std::sort(qwq, qwq + p);
    l = r = -1;
    re (i, 0, p) {
        const Query &q = qwq[i];
        while (q.l < l)
            ans -= cr[a[l]], --cl[a[l]], --l;
        while (q.r < r)
            ans -= cl[a[r]], --cr[a[r]], --r;
        while (l < q.l)
            ++l, ++cl[a[l]], ans += cr[a[l]];
        while (r < q.r)
            ++r, ++cr[a[r]], ans += cl[a[r]];
        q.add ? *q.ans += ans : (*q.ans -= ans);
    }
    re (i, 0, m)
        printf("%lld\n", res[i]);

    return 0;
}
