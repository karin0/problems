#include <akari>

IO<5000, 5000> io;

ll f[31][2][2][2][2];
int a, b, c;
ll dp(int p, bool ca, bool cb, bool oa, bool ox) {
    if (p < 0)
        return 1;
    ll &r = f[p][ca][cb][oa][ox];
    if (r)
        return r;
    int ta = ca ? a >> p & 1 : 1;
    int tb = cb ? b >> p & 1 : 1;
    int cl = c >> p & 1;
    rep (i, 0, ta) rep (j, 0, tb) {
        int x = i & j, y = i ^ j;
        if ((!oa || x <= cl) && (!ox || y >= cl))
            r += dp(p - 1, ca && i == ta, cb && j == tb, oa && x == cl, ox && y == cl);
    }
    return r;
}
int main() {
    int t;
    io >> t;
    re (_, 0, t) {
        io >> a >> b >> c;
        if (_)
            memset(f, 0, sizeof(f));
        io << (ll)a * b - dp(30, 1, 1, 1, 1) + std::max(a - c + 1, 0) + std::max(b - c + 1, 0) daze;
        // 0!
    }
    return 0;
 }
