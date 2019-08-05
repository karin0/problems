#include <cstdio>
#include <algorithm>

const int MAXN = 100005, INF = 2147483600;
int n, m, k, x[MAXN], y[MAXN], my[MAXN], mx[MAXN], f[MAXN], cx[MAXN], cy[MAXN], b[MAXN];

inline bool qaq(int p, int q) {
    return f[p] > f[q];
}

int main() {
    static int t, i, cnt, ans;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d", &n, &m, &k);
        cnt = 0;
        ans = 0;
        for (i = 1; i <= n; ++i)
            my[i] = INF, cx[i] = 0;
        for (i = 1; i <= m; ++i)
            mx[i] = INF, cy[i] = 0;
        for (i = 1; i <= k; ++i) {
            scanf("%d%d", x + i, y + i);
            my[x[i]] = std::min(my[x[i]], y[i]);
            mx[y[i]] = std::min(mx[y[i]], x[i]);
            ++cx[x[i]];
            ++cy[y[i]];
        }
        for (i = 1; i <= k; ++i) {
            b[i] = i;
            if (x[i] == mx[y[i]] && y[i] == my[x[i]])
                f[i] = cx[x[i]] + cy[y[i]];
        }
        std::sort(b + 1, b + k + 1, qaq);
        for (i = 1; i <= k; ++i) {
            if (!f[b[i]t)
                break;
            printf("Meet %d with %d\n", b[i], f[b[i]]);
            cnt += f[b[i]];
            ++ans;
        }
        printf("%d\n", cnt == k ? ans : -1);
    }
    return 0;
}
