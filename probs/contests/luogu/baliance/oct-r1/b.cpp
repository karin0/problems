#include <cstdio>
#include <algorithm>
using std::max;
using std::min;

typedef long long ll;
const int MAXN = 100005;
int n, a[3][MAXN], f[4][MAXN];

int main() {
    static int i, j, k, ans = 1;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i)
        scanf("%d", a[0] + i);
    for (i = 1; i <= n; ++i)
        scanf("%d", a[1] + i);
    for (i = 1; i <= n; ++i)
        scanf("%d", a[2] + i);
    for (i = 1; i <= n; ++i) {
        f[0][i] = 1;
        f[1][i] = 1;
        f[2][i] = 1;
        f[3][i] = 1;
        for (j = 1; j < i; ++j) {
            for (k = 0; k <= 3; ++k) {
                if (a[0][i] >= a[k][j])
                    f[0][i] = max(f[0][i], f[k][j] + 1);
                if (a[1][i] <= a[k][j])
                    f[1][i] = max(f[1][i], f[k][j] + 1);
            }
            for (k = 0; k <= 1; ++k) {
                if (a[2][i] <= a[k][j])
                    f[2][i] = max(f[2][i], f[k][j] + 1);
                if (a[2][i] >= a[k][j])
                    f[3][i] = max(f[3][i], f[k][j] + 1);
            }
            if (a[0][i] >= a[2][j])
                f[0][i] = max(f[0][i], max(f[2][j], f[3][j]) + 1);
            if (a[1][i] <= a[2][j])
                f[1][i] = max(f[1][i], max(f[2][j], f[3][j]) + 1);
            if (a[2][i] <= a[2][j])
                f[2][i] = max(f[2][i], f[2][j] + 1);
            if (a[2][i] >= a[2][j])
                f[3][i] = max(f[3][i], f[3][j] + 1);
        }
        ans = max(ans, max(max(f[0][i], f[1][i]), max(f[2][i], f[3][i])));
    }
    
    printf("%d\n", ans);
    return 0;
}
