#include <cstdio>

const int N = 1305;
int a[N][N];

int main() {
    int t, m = 0;
    scanf("%d", &t);
    while (t >>= 1)
        ++m;
    a[0][0] = 1;
    a[0][1] = 1;
    a[1][0] = 1;
    a[1][1] = -1;
    for (int k = 1; k < m; ++k) {
        int n = 1 << k;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                a[n + i][j] = a[i][j];
                a[i][n + j] = a[i][j];
                a[n + i][n + j] = -a[i][j];
            }
        }
    }
    int n = 1 << m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i][j] < 0)
                putchar('-');
            putchar('1');
            putchar(' ');
        }
        putchar('\n');
    }

    return 0;
}