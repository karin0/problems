#include <cstdio>
#include <cmath>
#include <algorithm>

const int MAXN = 50005, MAXB = 17, INF = 0x7f7f7f7f;

int n, lg, yr[MAXN], st[MAXN][MAXB];
inline void init() {
    static int k;
    for (int j = 1; j <= lg; ++j) {
        for (int i = 1; i <= n; ++i) {
            if ((k = i + (1 << (j - 1))) > n)
                break;
            st[i][j] = std::max(st[i][j - 1], st[k][j - 1]);
        }
    }
}
inline int query(int l, int r) {
    static int k;
    if (r < l) // *** 当然不会写反这个了
        return -INF;
    k = floor(log2(r - l + 1));
    return std::max(st[l][k], st[r - (1 << k) + 1][k]);
}

int main() {
    int m, i, qaq, x, y, l, r;
    scanf("%d", &n);
    lg = ceil(log2(n));
    for (i = 1; i <= n; ++i)
        scanf("%d%d", yr + i, &st[i][0]);
    init();
    scanf("%d", &m);
    for (qaq = 1; qaq <= m; ++qaq) {
        scanf("%d%d", &y, &x);
        l = std::lower_bound(yr + 1, yr + n + 1, y) - yr;
        r = std::lower_bound(yr + 1, yr + n + 1, x) - yr;
        if (yr[l] == y && yr[r] == x) {
            // printf("[%d]\n", query(l + 1, r - 1));
            if(r - l == x - y) // 全部已知
                puts((st[l][0] >= st[r][0] && query(l + 1, r - 1) < st[r][0]) ? "true" : "false");
            else
                puts((st[l][0] < st[r][0] || query(l + 1, r - 1) >= st[r][0]) ? "false" : "maybe");
        } else {
            if ((yr[r] == x && query(l, r - 1) >= st[r][0]) || (yr[l] == y && st[l][0] <= query(l + 1, r - 1)))
                puts("false");
            else
                puts("maybe");
        }
    }


    return 0;
}
