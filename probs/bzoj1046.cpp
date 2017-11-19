#include <cstdio>
#include <algorithm>
 
const int MAXN = 10020;
int n, a[MAXN], f[MAXN], pos[MAXN];
 
int main() {
    int m, q, i, k, lis, left, prev;
    scanf("%d", &n);
    for (i = n; i >= 1; --i)
        scanf("%d", a + i), a[i] = -a[i];
    f[1] = a[1];
    lis = 1;
    pos[n] = 1;
    for (i = 2; i <= n; ++i) {
        pos[n - i + 1] = 1;
        k = std::lower_bound(f + 1, f + lis + 1, a[i]) - f;
        f[k] = a[i];
        pos[n - i + 1] = k;
        lis = std::max(lis, k);
    }
    scanf("%d", &m);
    while (m--) {
        scanf("%d", &q);
        if (q > lis)
            printf("Impossible\n");
        else {
            left = q;
            prev = 0;
            for (i = 1; i <= n && left; ++i)
                if (pos[i] >= left && (prev == 0 || a[n - i + 1] < a[n - prev + 1]))
                    printf("%d%c", -a[n - i + 1], left == 1 ? '\n' : ' '), prev = i, --left;
        }
    }
    return 0;
}
