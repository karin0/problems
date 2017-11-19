#include <cstdio>
#include <cmath>

typedef long long ll;

inline ll sq(ll x) {
    static ll sqr;
    sqr = round(sqrt(x));
    return sqr * sqr == x ? sqr : -1;
}
inline ll gcd(ll x, ll y) {
    return y ? gcd(y, x % y) : x;
}


inline ll calc(ll r) {
    static ll d, a, us, u, v, res;
    res = 0;
    d = r << 1;
    for (ll g = 1; g * g <= d; ++g) {
        if (d % g == 0) {
            a = d / g;
            for (u = 1; (us = u * u) <= a; ++u) {
                v = sq(a - us);
                if (v != -1) {
                    if (u >= v)
                        break;
                    if (gcd(u, v) == 1)
                        ++res;
                }
            }

            a = g;
            for (u = 1; (us = u * u) <= a; ++u) {
                v = sq(a - us);
                if (v != -1) {
                    if (u >= v)
                        break;
                    if (gcd(u, v) == 1)
                        ++res;
                }
            }
        }
    }
    return res;
}

int main() {
    static ll r;
    scanf("%lld", &r);
    printf("%lld\n", (calc(r) + 1) << 2);
    return 0;
}
