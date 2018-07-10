#include <cstdio>
#include <algorithm>

const int MAXN = 16, MAXK = 103;

int k, n, u;
int req[MAXN], score[MAXN];
double f[MAXK][1 << MAXN], ans = 0.0;

int main() {
    int i, j, s, t;
    scanf("%d%d", &k, &n);
    u = (1 << n) - 1;
    for (i = 0; i < n; ++i) {
        scanf("%d", score + i);
        while (true) {
            scanf("%d", &t);
            if (t)
                req[i] |= 1 << (t - 1);
            else
                break;
        }
    }
    
    for (i = k; i >= 1; --i) {
        for (s = 0; s <= u; ++s) {
            for (j = 0; j < n; ++j) {
                if ((s | req[j]) == s) {
                    f[i][s] += std::max(f[i + 1][s], f[i + 1][s | (1 << j)] + score[j]);
                } else {
                    f[i][s] += f[i + 1][s];
                }
            }
            f[i][s] /= n;
        }
    }
    
    printf("%.6lf\n", f[1][0]);

    return 0;
}
