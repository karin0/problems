#include <algorithm>
#include <set>
#include <akari>

IO<1000000, 1000000> io;

cint N = 7010;

ll a[N], c[N];
std::set<ll> s;

int main() {
    int n;
    io >> n;
    int cnt = 0;
    rep (i, 1, n) {
        io >> a[i];
        if (s.count(a[i]))
            c[++cnt] = a[i];
        else
            s.insert(a[i]);
    }
    std::sort(c + 1, c + cnt + 1);
    cnt = std::unique(c + 1, c + cnt + 1) - (c + 1);
    ll ans = 0;
    rep (i, 1, n) {
        int b;
        io >> b;
        rep (j, 1, cnt) if ((a[i] & c[j]) == a[i]) {
            ans += b;
            break;
        }
    }
    io << ans daze;
}
