#include <cstdio>
#include <algorithm>

typedef long long ll;
ll n, k;
ll count(ll x) { // n! 含有几个 k, k 为素数
    static ll res, p;
    res = 0;
    p = x;
    while (p <= n && p >= 2) {
        res += n / p;
        p *= x;
    }
    return res;
}

ll solve() {
    static ll i, res;
    static int cnt;
    res = 1L << 60;
    cnt = 0;
    for (i = 2; i * i <= k; ++i) {
        if (k % i == 0) {
            cnt = 0;
            while (k % i == 0)
                ++cnt, k /= i;
            res = std::min(res, count(i) / cnt);
            if (res == 0)
                return 0;
        }
    }
    if (k > 1)
        return std::min(res, count(k));
    return res;
}

int main() {
    scanf("%lld%lld", &n, &k);
    printf("%lld\n", solve());

    return 0;
}
