#include <cstdio>

const int MAXN = 100005;
int n, cnt = 2, a, pa;
int main() {
    static int i;
    static bool inc;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &a);
        if (i == 1) {
            pa = a;
            continue;
        } else if (i == 2)
            inc = pa <= a;
        else if (inc && pa > a)
            ++cnt, inc = false;
        else if (!inc && pa < a)
            ++cnt, inc = true;
        pa = a;
    }
    /*
    for (i = 1; i <= bcnt; ++i)
        printf("%d ", b[i]);*/
    printf("%d\n", cnt);

    return 0;
}
