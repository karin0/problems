#include <bits/stdc++.h>

const int N = 2003;
int a[N][N];
int t[N * N], cc = 0;
int main() {
    int n = 10, k = 0;
    int i = 0, l = 1;
    for (int i = 1; i <= 10000; ++i)
        t[i] = i;
    while (i <= n + n) {
        int x = i;
        int y = 0;
        while (x >= 0 || y < n) {
            // print(x, y)
            // fprintf(stderr, "%d %d %d\n", i, x, y);
            if (x >= 0 && y < n && x < n && y >= 0)
                a[x][y] = 1, ++k;
            x -= 1;
            y += 1;
        }
        if (--l == 0) {
            i += t[++cc];
            l = 1;
        }
        i += 1;
    }
    printf("%d\n", n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            printf("%d", a[i][j]);
        putchar('\n');
    }
    printf("%d\n", k);
}