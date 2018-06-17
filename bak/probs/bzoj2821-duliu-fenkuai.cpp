#include <cstdio>
#include <cmath>
#include <algorithm>

const int N = 100001;
int n, c, bcnt, bsiz, a[N], f[321][321], g[321][N], cnt[N];
inline int bel(int i) {
    return (i - 1) / bsiz + 1;
}
void init() {
    static int i, j, ans, x, k;
    bsiz = sqrt(n);
    bcnt = n / bsiz;
    if (bsiz * bcnt < n)
        ++bcnt;
    for (i = 1; i <= bcnt; ++i) {
        std::fill(cnt + 1, cnt + c + 1, 0);
        ans = 0;
        for (j = (i - 1) * bsiz + 1; j <= n; ++j) {
            x = a[j];
            if (cnt[x] & 1)
                ++ans;
            else if (cnt[x] > 0)
                --ans;
            ++cnt[x];
            if (j % bsiz == 0) {
                k = j / bsiz;
                f[i][k] = ans;
                if (i == 1)
                    for (x = 1; x <= c; ++x)
                        g[k][x] = cnt[x];
            } else if (j == n) {
                f[i][bcnt] = ans;
                if (i == 1)
                    for (x = 1; x <= c; ++x)
                        g[bcnt][x] = cnt[x];
            }
        }
    }
}
int query(int l, int r) {
    static int i, x, ans, lb, rb;
    if (bel(l) == bel(r)) {
        if ((l - 1) % bsiz == 0 && (r % bsiz == 0 || r == n))
            return f[r / bsiz][r / bsiz];
        ans = 0;
        for (i = l; i <= r; ++i)
            cnt[a[i]] = 0;
        for (i = l; i <= r; ++i) {
            x = a[i];
            if (cnt[x] & 1)
                ++ans;
            else if (cnt[x] > 0)
                --ans;
            ++cnt[x];
        }
        return ans;
    }
    lb = bel(l) + bool((l - 1) % bsiz);
    rb = bel(r) - bool(r % bsiz && r != n);
    for (i = l; i <= (lb - 1) * bsiz; ++i) {
        x = a[i];
        cnt[x] = g[rb][x] - g[lb - 1][x];
    }
    for (i = rb * bsiz + 1; i <= r; ++i) {
        x = a[i];
        cnt[x] = g[rb][x] - g[lb - 1][x];
    }
    ans = f[lb][rb];
    for (i = l; i <= (lb - 1) * bsiz; ++i) {
        x = a[i];
        if (cnt[x] & 1)
            ++ans;
        else if (cnt[x] > 0)
            --ans;
        ++cnt[x];
    }
    for (i = rb * bsiz + 1; i <= r; ++i) {
        x = a[i];
        if (cnt[x] & 1)
            ++ans;
        else if (cnt[x] > 0)
            --ans;
        ++cnt[x];
    }
    return ans;
}

int main() {
    static int m, i, ans, l, r;
    scanf("%d%d%d", &n, &c, &m);
    for (i = 1; i <= n; ++i)
        scanf("%d", a + i);
    init();
    while (m--) {
        scanf("%d%d", &l, &r);
        l = (l + ans) % n + 1;
        r = (r + ans) % n + 1;
        if (l > r)
            std::swap(l, r);
        printf("%d\n", ans = query(l, r));
    }

    return 0;
}
