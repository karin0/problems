#include<cstdio>

const int MAXN = 100005, MAXV = 1000005;

int n, a[MAXN], cnt[MAXV];

int main() {
    static int i, j, v, ans;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i)
        scanf("%d", a + i), ++cnt[a[i]];
    for (i = 1; i <= n; ++i) {
        v = a[i];
        ans = -1; // itself is considered
        for (j = 1; j * j <= v; ++j)
            if (v % j == 0) {
                ans += cnt[j];
                if (j * j < v)
                    ans += cnt[v / j];
            }
        printf("%d\n", ans);
    }

    return 0;
}
