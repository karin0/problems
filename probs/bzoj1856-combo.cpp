#include <cstdio>

typedef long long ll;
const int mo = 20100403;
ll pow(ll a, int x) {
    static ll res;
    for (res = 1; x; a = a * a % mo, x >>= 1)
        if (x & 1)
            res = res * a % mo;
    return res;
}
ll inv(ll a) {
    return pow(a, mo - 2);
}
ll fact(ll a) {
    static int cnt = 1, i;
    static ll fac[2000005] = {1, 1};
    if (a <= cnt)
        return fac[a];
    for (i = cnt + 1; i <= a; ++i)
        fac[i] = fac[i - 1] * i % mo;
    cnt = a;
    return fac[a];
}
ll combo(ll n, ll k) {
    return fact(n) * inv(fact(k) * fact(n - k) % mo) % mo;
}

int main() {
    ll n, m;
    scanf("%lld%lld", &n, &m);
    printf("%lld\n", (combo(n + m, m) - combo(n + m, m - 1) + mo) % mo);
    return 0;
}
