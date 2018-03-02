#include <cstdio>
#include <algorithm>

const int MAXN = 100002;
int n, cnt, a[MAXN], ind[MAXN];
bool used[MAXN];

int main() {
    int i, x;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i)
        scanf("%d", a + i), ind[a[i]] = i;
    used[n + 1] = true;
    for (x = n; x >= 1; --x) {
        i = ind[x];
        if (used[i] || used[i + 1])
            continue;
        used[i] = true;
        used[i + 1] = true;
        cnt += 2;
        printf("%d %d%c", x, a[i + 1], (cnt == n) ? '\n' : ' ');
    }

    return 0;
}
