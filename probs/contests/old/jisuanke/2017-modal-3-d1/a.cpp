#include <cstdio>
#include <algorithm>

int n, m, a[6], sa, save, left;
double cp;

void sfd(int pos, int sum, double p) {
    int ub = std::min(a[pos], left - sum);
    if (pos == n) {
        if (left - sum <= a[pos])
            cp += p / (a[n] + 1);
        return;
    }
    for (int i = ((pos == save) ? 1 : 0); i <= ub; ++i)
        sfd(pos + 1, sum + i, p / (a[pos] + (pos == save ? 0 : 1)));
}

int main() {
    int i, j, y;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i)
        scanf("%d", a + i), sa += a[i];
    left = sa - m;
    if (left <= 0) {
        for (i = 1; i <= n; ++i)
            puts("0.000000\n");
        return 0;
    }
    if (n == 1) {
        puts("1.000000\n");
        return 0;
    }
    for (save = 1; save <= n; ++save) {
        cp = 0.0;
        sfd(1, 0, 1.0);
        printf("%.6lf\n", cp);
    }

    return 0;
}
