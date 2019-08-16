#include <akari>

IO<1000000, 10> io;

cint N = 100002, mo = 1000000007;

inline int inv(ll a, int n = mo - 2) {
    ll res = 1;
    for (; n; n >>= 1, a = a * a % mo)
        if (n & 1)
            res = res * a % mo;
    return res;
}

int cnt[N], f[N];
int main() {
    int n, b;
    io > n > b;
    if (n <= 0) {
        io << '0' daze;
        return 0;
    }
    f[0] = 1;
    int mx = 0;
    if (b == 1) {
        rep (i, 1, n) {
            int x;
            io >> x;
            ++cnt[x];
            mx = std::max(mx, x);
            f[i] = (ll)f[i - 1] * i % mo;
        }
    } else {
        int t = inv(b - 1), bp = 1;
        rep (i, 1, n) {
            int x;
            io >> x;
            ++cnt[x];
            mx = std::max(mx, x);
            f[i] = (ll)f[i - 1] * ((bp = (ll)bp * b % mo) - 1) % mo * t % mo;
        }
    }
    int r = 1;
    rep (i, 0, mx) if (cnt[i] > 1)
        r = (ll)r * f[cnt[i]] % mo;
    (io < int((ll)f[n] * inv(r) % mo)) daze;
}
