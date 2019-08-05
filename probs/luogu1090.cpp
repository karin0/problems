#include <cstdio>
#include <algorithm>

const int N = 10003;
int main() {
    static int n, a[N], i, j, ans;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i)
        scanf("%d", a + i);
    std::sort(a + 1, a + n + 1);
    for (i = 2; i <= n; ++i) {
        a[i] += a[i - 1];
        ans += a[i];
        for (j = i; j < n && a[j] > a[j + 1]; ++j)
            std::swap(a[j], a[j + 1]);
    }
    printf("%d\n", ans);

    return 0;
}
