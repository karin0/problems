#include <akari>
typedef long long ll;

inline ll qmul(ll x, ll y, ll m) {
    ll tmp = x * y - ((ll)((long double)x / m * y + 0.5)) * m;
    return tmp < 0 ? tmp + m : tmp;
}

inline ll qpow(ll x, ll n, ll m) {
    ll r = 1;
    for (; n; n >>= 1, x = qmul(x, x, m))
        if (n & 1)
            r = qmul(r, x, m);
    return r;
}

const int pris[10] = { 3, 5, 7, 11, 13, 17, 19, 23 }, pris_n = 8;

inline bool is_prime(ll n) {
    if (n == 2)
        return true;
    if (n == 1 || !(n & 1))
        return false;
    ll t = n - 1;
    int k = 0;
    while (!(t & 1))
        t >>= 1, ++k;
    re (i, 0, pris_n) {
        if (n == pris[i])
            return true;
        ll x = qpow(pris[i], t, n), y = x;
        rep (j, 1, k) {
            x = qmul(x, x, n);
            if (x == 1 && !(y == 1 || y == n - 1))
                return false;
            y = x;
        }
        if (x != 1)
            return false;
    }
    return true;
}
// doc_begin
// 
// tmpl_end
// LOJ 143

int main() {
    ll n;
    while (scanf("%lld", &n) == 1)
        puts(is_prime(n) ? "Y" : "N");
}
