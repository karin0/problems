#include <akari>

inline ll f(ll n, ll k, ll m) {
    m = n - m;
    if (k <= 1)
        return n - m;
    ll i = m;
    while (i < n) {
        ll r = (i - m + k - 2) / (k - 1);
        if ((i + r) > n)
            r = n - i;
        else if (!r)
            r = 1;
        i += r;
        m = (m + (r * k)) % i;
    }
    return m + 1;
}

IO<1000000, 1000000> io;

int main() {
    int T;
    io >> T;

    rep (ks, 1, T) {
        ll n, m, k;
        io >> n >> m >> k;

        io << "Case #" << ks << ": " << f(n, k, m) << '\n';
    }
}