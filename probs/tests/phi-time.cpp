#include <cstdio>
#include <math.h>
#include <sys/time.h>

typedef long long ll;

inline ll phi(ll x) {
    static ll i, cnt, res;
    for (res = x, cnt = 0, i = 2; i * i <= x; ++i) {
        ++cnt;
        if (x % i == 0) {
            res -= res / i;
            ++cnt;
            while (x % i == 0)
                x /= i, ++cnt;
        }
    }
    return cnt;
}
ll laugh(ll x) {
    return x * x;
}
int main() {
    static int t, ks;
    static ll p, tmp, i;
    struct timeval start;
    struct timeval end;
    unsigned long timer;
    // mem[1] = 1;
    scanf("%d", &t);
    for (ks = 0; ks < t; ++ks) {
        scanf("%lld", &p);
        gettimeofday(&start, NULL);
        for (i = 1; i <= 2; ++i) {
            tmp = phi(p);
            tmp = laugh(tmp);
        }
        gettimeofday(&end, NULL);
        timer = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
        printf("%lf\n", timer / log2(p));

    }
    return 0;
}
