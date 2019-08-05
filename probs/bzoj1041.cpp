#include <cstdio>
#include <cmath>

typedef long long ll;

inline ll gcd(ll x, ll y) {
    return y == 0 ? x : gcd(y, x % y);
}

int main() {
    ll r, g, b1, ans = 0, u, vv, v;
    scanf("%lld", &r);
    for (g = 1; g * g <= 2 * r; ++g) {
        if (!((2 * r) % g)) {
            b1 = 2 * r / g;
            for (u = 1; u * u <= b1; ++u) {
                vv = b1 - u * u;
                v = round(sqrt(vv));
                if (u < v && v * v == vv && gcd(u * u, vv) == 1)
                    ++ans;
            }
            b1 = g;
            for (u = 1; u * u <= b1; ++u) {
                vv = b1 - u * u;
                v = round(sqrt(vv));
                if (u < v && v * v == vv && gcd(u * u, vv) == 1)
                    ++ans;
            }
        }
    }
    printf("%lld", (ans + 1) * 4);

    return 0;
}
