#include <akari>

IO<1000000, 1000000> io;

cint N = 100002;

int main() {
    int n, cneg = 0;
    ll ans = 0; // ***
    io > n;
    bool vis0 = false;
    rep (i, 1, n) {
        int x;
        io >> x;
        if (x > 0)
            ans += x - 1;
        else if (x < 0)
            ++cneg, ans += -x - 1;
        else
            vis0 = true, ++ans;
    }
    io << ((vis0 || !(cneg & 1)) ? ans : ans + 2) daze;

    return 0;
}
