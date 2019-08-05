/*
f(i, j) := 击杀生命为 i, 防御为 j 的怪物需要的最少代价
f(i, j) = min{
                min{ f(i - atk[k], j) + cost[k] | i >= atk[k] },
                min{ cost[k] | i < atk[k] }
             }
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
const long long INF = 6e17;
const int MAXN = 100010, MAXM = 1010, MAXA = 1010, MAXB = 15;

int n, m;
int hp[MAXN], def[MAXN], cost[MAXM], atk[MAXM];
//  a         b          k           p
long long f[MAXA][MAXB];

void read(int &res) {
    res = 0;
    char ch = 0;
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9') {
        res = res * 10 + ch - '0';
        ch = getchar();
    }
}

int main() {
    register int i, j, k, def_max, atk_max, hp_max, hurt;
    long long ans;
    while (scanf("%d%d", &n, &m) == 2) {
        def_max = atk_max = hp_max = -233;
        ans = 0;
        for (i = 1; i <= n; ++i)
            read(hp[i]),
            read(def[i]),
            def_max = std::max(def_max, def[i]),
            hp_max = std::max(hp_max, hp[i]);
        for (i = 1; i <= m; ++i)
            read(cost[i]),
            read(atk[i]),
            atk_max = std::max(atk_max, atk[i]);
        if (atk_max < def_max) {
            printf("-1\n");
            continue;
        }
        for (j = 0; j <= 11; ++j)
            f[0][j] = 0;
        for (j = 0; j <= 11; ++j)
            for (i = 1; i <= 1005; ++i) {
                f[i][j] = INF;
                for (k = 1; k <= m; ++k)
                    if ((hurt = atk[k] - j) > 0)
                        f[i][j] = std::min(f[i][j], 
                            ((i > hurt) ? f[i - hurt][j] : 0) + cost[k]
                            );
            }

        bool fail = false;
        for (i = 1; i <= n; ++i) {
            if (f[hp[i]][def[i]] >= INF) {
                printf("-1\n");
                fail = true;
                break;
            }
            ans += f[hp[i]][def[i]];
        }
        if (fail)
            continue;
        printf("%I64d\n", ans); // Windows is Dust
    }

    return 0;
}
