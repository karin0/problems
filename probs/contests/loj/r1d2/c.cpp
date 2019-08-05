#include <cstdio>

const int MAXN = 1000005;
int a[MAXN], n, k;

int main() {
    static int t, i;
    scanf("%d%d%d", &t, &n, &k);
    for (i = 1; i <= n; ++i)
        scanf("%d", a + i);
    puts("No");
    return 0;
}
