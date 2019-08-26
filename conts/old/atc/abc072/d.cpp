#include <cstdio>

const int MAXN = 1e5 + 5;
int n, a[MAXN], cnt;
bool bad[MAXN];

int main() {
    int i;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d", a + i);
        if (a[i] == i)
            bad[i] = true;
    }
    for (i = 1; i <= n; ++i) {
        if (bad[i]) {
            if (bad[i + 1])
                bad[i + 1] = false, ++cnt;
            else if (i != a[i - 1])
                    ++cnt;
            else {
                ++cnt;
            }

        }
    }
    printf("%d\n", cnt);
    return 0;
}
