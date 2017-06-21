#include <cstdio>

    static int a[100000][200000];
int main() {
    a[1][2] = 114;
    a[9191][19191] = 514;
    printf("%d\n", a[1][2] + a[9191][19191]);

    return 0;
}
