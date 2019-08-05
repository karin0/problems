#include <cstdio>
#include <algorithm>

const int MAXN = 100005;
int n, maxi[MAXN][20], lb[MAXN];
void init() {
    static int i, j, k;
    // maybe calcing maxi[i][0] is necessery
    k = 0;
    for (i = 1; i <= n; ++i)
        lb[i] = (1 << (k + 1)) == i ? ++k : k; // ***
    k = lb[n];
    for (j = 1; j <= k; ++j)
        for (i = 1; i + (1 << (j - 1)) <= n; ++i)
            maxi[i][j] = std::max(maxi[i][j - 1], maxi[i + (1 << (j - 1))][j - 1]);
}
int query(int l, int r) {
    static int k;
    // if (r < l)
    //    return -INF;
    k = lb[r - l + 1];
    return std::max(maxi[l][k], maxi[r - (1 << k) + 1][k]);
}

int main() {
    static int m, i, l, r;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i)
        scanf("%d", maxi[i] + 0); // to avoid a[]
    init();
    for (i = 1; i <= m; ++i)
        scanf("%d%d", &l, &r), printf("%d\n", query(l, r));

    return 0;
}
