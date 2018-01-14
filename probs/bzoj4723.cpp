#include <cstdio>
#include <climits>
#include <algorithm>

typedef long long ll;
int main() {
    static ll n, dest, i, klb, kub, x, ylb, yub, dx, t;
    static bool fail;
    scanf("%lld%lld", &n, &dest);
    klb = 0, kub = 0, x = 0;
    for (i = 1; i <= n; ++i) {
        // printf("2k in (%lld, %lld)\n", klb, kub);
        scanf("%lld%lld%lld", &t, &ylb, &yub); // x; y \in (lb, hb);
        if (fail)
            continue;
        dx = t - x, x = t;
        klb = std::max(klb - dx, ylb + 1);
        kub = std::min(kub + dx, yub - 1);
        if ((klb & 1) != (x & 1))
            ++klb;
        if ((kub & 1) != (x & 1))
            --kub;
        if (kub < klb) {
            puts("NIE");
            fail = true;
        }
    }
    if (fail)
        return 0;
    printf("%lld\n", (klb + x) >> 1);
}
