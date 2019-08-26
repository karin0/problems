#include <cstdio>

const int MAXN = 5005;

int n, m, ans;
int w[MAXN][MAXN];

int main() {
    int i, j, k;
    scanf("%d%d", &n, &m);
    while (m--) {
        scanf("%d%d%d", &i, &j, &k);
        w[i][j] = w[j][i] = k;
    }
    for (i = 1; i <= n; ++i) {
        for (j = i + 1; j <= n; ++j) {
            for (k = j + 1; k <= n; ++k) {
                if (w[i][j] == w[j][k] && w[i][j] == w[i][k])
                    ans -= 6;
                else if (w[i][j] != w[j][k] && w[i][j] != w[i][k] && w[j][k] != w[i][k])
                    ans += 3;
            }
        }
    }
    
    printf("%d\n", ans);
    return 0;
}
