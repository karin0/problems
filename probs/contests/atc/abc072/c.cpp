#include <cstdio>
#include <algorithm>

const int MAXN = 1e5 + 5;

int a, n, cnt[MAXN];

int main() {
    int i, x = -1;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &a);
        ++cnt[a + 1]; // all + 1
        ++cnt[a];
        ++cnt[a + 2];
    }
    for (i = 0; i < MAXN; ++i) {
        x = std::max(x, cnt[i]);
    }
    printf("%d", x);

    return 0;
}
