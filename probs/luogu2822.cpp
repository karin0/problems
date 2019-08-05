#include <cstdio>
#include <algorithm>

const int MAXN = 2005, MAXT = 1e5 + 5;

int k, c[MAXN][MAXN], ans[MAXN][MAXN];

struct Query {
    int n, m;
} qwq[MAXT];

int main() {
    int t, r, i, j, res, maxn = 1, maxm = 1;
    scanf("%d%d", &t, &k);
    for (i = 1; i <= t; ++i) {
        scanf("%d%d", &qwq[i].n, &qwq[i].m);
        maxn = std::max(maxn, qwq[i].n);
        maxm = std::max(maxm, qwq[i].m);
    }
    c[1][0] = 1;
    c[1][1] = 1;
    for (i = 2; i <= maxn; ++i) {
        c[i][0] = 1;
        r = std::min(i, maxm);
        res = 0;
        for (j = 1; j <= r; ++j) {
            c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
             if (c[i][j] >= k)
                 c[i][j] -= k;

            if (c[i][j] == 0)
                ++res;
            // printf("%d %d = %d\n", i, j, c[i][j]);
            ans[i][j] = res + ans[i - 1][j > i - 1 ? i - 1 : j];
        }
    }
    for (i = 1; i <= t; ++i)
        printf("%d\n", ans[qwq[i].n][std::min(qwq[i].m, qwq[i].n)]);

    return 0;
}
/*
１
２　１
３　３　１
４　６　４　１
５　10　10　５　１
６　15　20　15　６　１
７　21　35　35　21　７　１
８　28　56　70　56　28　８　１
*/
