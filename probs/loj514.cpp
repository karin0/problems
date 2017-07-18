#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 10010
#define INF 2147483640

int n, a[MAXN], s[MAXN], ans[MAXN];

void read(int& data) {
    bool neg;
    char ch = 0;
    data = 0;
    while (ch != '-' && (ch < '0' || ch > '9'))
        ch = getchar();
    if (ch == '-')
        ch = getchar(), neg = true;
    else
        neg = false;
    while (ch >= '0' && ch <= '9') {
        data = data * 10 + (ch - '0');
        ch = getchar();
    }
    if (neg) data *= -1;
}

int main() {
    register int q, i, j, x;
    read(n);
    read(q);
    std::fill(ans, ans + n + 1, -INF);
    for (i = 1; i <= n; ++i) {
        read(a[i]);
        s[i] = s[i - 1] + a[i];
    }
    for (i = 1; i <= n; ++i)
        for (j = 1; i + j - 1 <= n; ++j)
            ans[j] = std::max(ans[j], s[i + j - 1] - s[i - 1]);
    for (i = n - 1; i >= 1; --i)
        ans[i] = std::max(ans[i], ans[i + 1]);
    while (q--) {
        scanf("%d", &x);
        printf("%d\n", ans[x]);
    }
    return 0;
}
