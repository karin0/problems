#include <cstdio>

const int N = 100002;
int a[N], p[N], pre[N];

int main() {
    int n;
    long long ans = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        if (p[a[i]])
            pre[i] = p[a[i]];
        p[a[i]] = i;
        ans += (long long)(i - (pre[i] + 1) + 1) * (n - i + 1);
    }

    printf("%lld\n", ans);

    return 0;
}