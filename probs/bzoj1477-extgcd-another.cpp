#include <cstdio>

typedef long long ll;

inline void extgcd(ll a, ll b, ll &g, ll &x, ll &y) {
    b ? (extgcd(b, a % b, g, y, x), y -= x * (a / b)) : (g = a, x = 1, y = 0);
}

int main() {
    ll x, y, m, n, l, t, k, g, tt;
    scanf("%lld%lld%lld%lld%lld", &x, &y, &m, &n, &l);
    // extgcd(n - m, l, g, t, k);
    extgcd(m - n, -l, g, t, k);
    if ((y - x) % g) {
        puts("Impossible\n");
        return 0;
    }
    t = t * (y - x) / g;
    t = (t % l + l) % l;

    printf("%lld\n", t);
    return 0;
}
