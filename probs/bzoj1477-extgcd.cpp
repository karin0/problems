#include <cstdio>

typedef long long ll;

inline void extgcd(ll a, ll b, ll &g, ll &x, ll &y) {
    b ? (extgcd(b, a % b, g, y, x), y -= x * (a / b)) : (g = a, x = 1, y = 0);
}

int main() {
    ll x, y, m, n, l, t, k, g, tt;
    scanf("%lld%lld%lld%lld%lld", &x, &y, &m, &n, &l);
    extgcd(n - m, l, g, t, k);
    if ((x - y) % g) {
        puts("Impossible\n");
        return 0;
    }
    t = t * (x - y) / g;
    t = (t % l + l) % l;
    
    printf("%lld\n", t);
    return 0;
}
