#include <cstdio>
#include <algorithm>

const int MAXN = 1005;

inline int lis(int *arr, int len) {
    static int f[MAXN];
    int ans = 1, k;
    f[1] = arr[1];
    for (int i = 2; i <= len; ++i) {
        k = std::lower_bound(f + 1, f + ans + 1, arr[i]) - f;
        /*for (int j = 1; j <= ans; ++j)
            printf("*%d ", f[j]);
        printf("\ni = %d, a[i] = %d, k = %d, f[k] = %d, ans is %d\n", i, arr[i], k, f[k], ans);
        */
        if (k <= len) {
            f[k] = arr[i];
            ans = std::max(ans, k);
        }
    }
    return ans;
}

int a[MAXN];

int main() {
    int n, i;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i)
        scanf("%d", a + i);
    
    printf("%d\n", lis(a, n));
    return 0;
}
