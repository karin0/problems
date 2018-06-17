#include <cstdio>
#include <cmath>

typedef long long ll;
int main() {
    static int n;
    static ll l, r, x;
    static double p, v;
    scanf("%d", &n);
    --n;
    p = (double)n * std::log(10);
    l = 1, r = p;
    while (r - l > 1) {
        x = (l + r) >> 1;
        v = (double)x * std::log(x);
        if (std::abs(v - p) < 1e-5) {
            l = x;
            break;
        }
        if (v <= p)
            l = x;
        else
            r = x;
    }
    v = (double)l * std::log(l);
    if (std::abs(v - p) > 1e-5) {
        if (v < p)
            ++l;
        else
            --l;
    }
    printf("%lld\n", l);

    return 0;
}
