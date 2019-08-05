#include <cstdio>

int gcd(int x, int y) {
    return y == 0 ? x : gcd(y, x % y);
}
int exgcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int g = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return g;
}

int n = 3, a[4], m[4] = {0, 23, 28, 33}, inv[4] = {0, 6, 19, 2}, d;

int finv(int q, int mo) {
    static int x, y;
    exgcd(q, mo, x, y);
    return ((x % mo) + mo) % mo; // lhy orz
}

inline int crt() {
    int pm, i, mm[4], res, tmp;
    pm = 1;
    res = 0;
    for (i = 1; i <= n; ++i)
        pm *= m[i];
    for (i = 1; i <= n; ++i)
        mm[i] = pm / m[i];
    for (i = 1; i <= n; ++i)
        tmp = finv(mm[i], m[i]),
        res = (res + a[i] * mm[i] * tmp) % pm;
    while (res <= d)
        res += pm;
    return res; // lhy orz
}

int main() {
    for (int kase = 1; ; ++kase) {
        scanf("%d%d%d%d", a + 1, a + 2, a + 3, &d);
        if (d == -1)
            break;

        printf("Case %d: the next triple peak occurs in %d days.\n", kase, crt() - d);
    }


    return 0;
}
