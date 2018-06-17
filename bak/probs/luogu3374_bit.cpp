#include <cstdio>
#define LOWBIT(x) ((x) & (-(x)))
#define MAXN 500010
int n;
long long bit[MAXN];
void update(int x, long long v) {
    while (x <= n) {
        bit[x] += v;
        x += LOWBIT(x);
    }
}
long long query(int x) {
    long long res = 0;
    while (x > 0) {
        res += bit[x];
        x -= LOWBIT(x);
    }
    return res;
}

int main() {
    int q, opt, x, y;
    long long k;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &k);
        update(i, k);
    }
    while (q--) {
        scanf("%d%d", &opt, &x);
        if (opt - 1) {
            scanf("%d", &y);
            printf("%lld\n", query(y) - query(x - 1));
        }
        else {
            scanf("%lld", &k);
            update(x, k);
        }
    }

    return 0;
}
