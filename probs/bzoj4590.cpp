#include <cstdio>

const int MAXN = 100005;

int n, m;
long long a[MAXN];

bool suc;
inline int check(long long x) {
    static long long ccnt;
    static int acnt, i;
    ccnt = 0;
    acnt = 0;
    for (i = 1; i <= n; ++i) {
        ccnt += a[i];
        if (ccnt < 0)
            ccnt = 0;
        else if (ccnt >= x)
            ++acnt, ccnt = 0; // *** reset it
    }
    return acnt - m;
}

int main() {
    int i, d;
    long long x, lb, rb = 0, xmax;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i) {
        scanf("%lld", a + i);
        if (a[i] > 0)
            rb += a[i];
    }

    lb = 1, rb += 1;
    while (rb - lb > 1) { // [lb, rb) for max
        x = (lb + rb) >> 1;
        d = check(x);
        if (d > 0)
            lb = x + 1; // This is not suc.
        else if (d < 0)
            rb = x;
        else
            lb = x, suc = true;
    }
    if (!suc) {
        puts("-1");
        return 0;
    }
    xmax = lb;
    lb = 0, rb = xmax;
    while (rb - lb > 1) { // (lb, rb] for min
        x = (lb + rb) >> 1;
        d = check(x);
        if (d > 0)
            lb = x;
        else // d == 0
            rb = x;
    }

    printf("%lld %lld\n", rb, xmax);
    return 0;
}
