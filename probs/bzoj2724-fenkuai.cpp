#include <cstdio>
#include <cmath>
#include <algorithm>

const int N = 40002;
int n, c, bcnt, bsiz, a[N], f[202][202], g[202][N], cnt[N];
inline int bel(int i) {
    return (i - 1) / bsiz + 1;
}
void init() {
    static int i, j, ans, cm, x, k;
    bsiz = sqrt(n);
    bcnt = n / bsiz;
    if (bsiz * bcnt < n)
        ++bcnt;
    for (i = 1; i <= bcnt; ++i) {
        std::fill(cnt + 1, cnt + c + 1, 0);
        ans = cm = 0;
        for (j = (i - 1) * bsiz + 1; j <= n; ++j) {
            x = a[j];
            ++cnt[x];
            if (cnt[x] > cm || (cnt[x] == cm && x < ans))
                ans = x, cm = cnt[x];
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
    static int i, x, ans, cm, lb, rb;
    if (bel(l) == bel(r)) {
        if ((l - 1) % bsiz == 0 && (r % bsiz == 0 || r == n))
            return f[r / bsiz][r / bsiz];
        ans = cm = 0;
        for (i = l; i <= r; ++i)
            cnt[a[i]] = 0;
        for (i = l; i <= r; ++i) {
            x = a[i];
            ++cnt[x];
            if (cnt[x] > cm || (cnt[x] == cm && x < ans))
                ans = x, cm = cnt[x];
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
    cm = g[rb][ans] - g[lb - 1][ans];
    for (i = l; i <= (lb - 1) * bsiz; ++i) {
        x = a[i];
        ++cnt[x];
        if (cnt[x] > cm || (cnt[x] == cm && x < ans))
            ans = x, cm = cnt[x];
    }
    for (i = rb * bsiz + 1; i <= r; ++i) {
        x = a[i];
        ++cnt[x];
        if (cnt[x] > cm || (cnt[x] == cm && x < ans))
            ans = x, cm = cnt[x];
    }
    return ans;
}

int main() {
    static int m, i, ans, l, r, b[N], *p;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i)
        scanf("%d", a + i), b[i] = a[i];
    std::sort(b + 1, b + n + 1);
    p = std::unique(b + 1, b + n + 1);
    c = p - b - 1;
    for (i = 1; i <= n; ++i)
        a[i] = std::lower_bound(b + 1, p, a[i]) - b;
    init();
    while (m--) {
        scanf("%d%d", &l, &r);
        l = (l + ans - 1) % n + 1;
        r = (r + ans - 1) % n + 1;
        if (l > r)
            std::swap(l, r);
        printf("%d\n", ans = b[query(l, r)]);
    }

    return 0;
}
