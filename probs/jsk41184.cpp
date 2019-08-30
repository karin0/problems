#include <akari>

IO<1000000, 1000000> io;

std::map<std::pair<ll, ll>, int> ms, mt;

int main() {
    int T, n, k;
    io >> T;
    while (T--) {
        ms.clear();
        io >> n;
        int ans = 0;
        while (n--) {
            io >> k;
            rep (i, 1, k) {
                std::pair<ll, ll> x;
                io >> x.first >> x.second;
                ccc(n, i, x.first, x.second);
                if (!mt.count(x))
                    mt[x] = 1;
            }
            for (auto &p : ms)
                if (mt.count(p.first))
                    mt[p.first] += p.second;
            ms = mt;
            mt.clear();
            for (auto &p : ms)
                ans = std::max(ans, p.second);
        }
        io << ans daze;
    }
}
