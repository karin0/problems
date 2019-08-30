#include <akari>

IO<1000000, 1000000> io;

const int N = 50003;
std::set<int> sx, sy;

int ax[N], ay[N];
int main() {
    int n;
    io >> n;
    rep (i, 1, n)
        io >> ax[i] >> ay[i];
    ll ans = 0;
    per (i, n, 1) {
        int x = ax[i], y = ay[i];
        auto it = sx.lower_bound(x);
        ans += it == sx.begin() ? x : x - *std::prev(it);
        it = sy.lower_bound(y);
        ans += it == sy.begin() ? y : y - *std::prev(it);
        sx.insert(x);
        sy.insert(y);
    }
    io << ans daze;
}
