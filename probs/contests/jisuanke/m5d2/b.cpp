#include <cstdio>

const int MAXN = 500005;
int n, w[MAXN];

int main() {
    static int kase, d, q, c, k, r;
    scanf("%d%d", &n, &q);
    for (k = 1; k <= n; ++k)
        scanf("%d", w + k);
    for (kase = 0; kase < q; ++kase) {
        scanf("%d%d", &c, &k);
        r = -1;
        for (d = 0; ; ++d) {
            if (k + d > n && k - d < 1)
                break;
            if (k - d >= 1 && w[k - d] >= c) {
                r = k - d;
                break;
            }
            if (k + d <= n && w[k + d] >= c) {
                r = k + d;
                break;
            }
        }
        if (r == -1)
            puts("-1");
        else {
            w[r] -= c;
            printf("%d\n", r);
        }
    }

    return 0;
}
