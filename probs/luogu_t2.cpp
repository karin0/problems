#include <cstdio>

typedef long long ll;

ll a, b, c, cap, uni, sum;

int main() {
    ll i;
    while (scanf("%lld%lld%lld", &cap, &uni, &sum) == 3) {
        a = b = c = 0;
        for (i = 1; i <= uni; i <<= 1)
            if (i & uni) {
                if (i & cap)
                    a += i, b += i, c += i, sum -= 3 * i;
                else {
                    if (!(i & sum))
                        b += i, sum -= i;
                    c += i, sum -= i;
                }
            }
        printf("%lld %lld %lld\n", a, b, c);
    }
    return 0;
}
