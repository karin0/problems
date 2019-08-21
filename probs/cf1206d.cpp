#include <akari>

IO<1000000, 10> io;

cint N = 100002, inf = 0x3f3f3f3f;

ll a[N];
int cnt[70], d[131][131];
int main() {
    int n;
    io > n;
    int cc = 0;
    rep (i, 1, n) {
        ll x;
        io > x;
        if (x) {
            a[++cc] = x;
            for (int j = 0; x; ++j, x >>= 1)
                if ((x & 1) && ++cnt[j] >= 3)
                    return io << '3' daze, 0;
        }
    }
    n = cc;
    rep (i, 1, n) {
        re (j, 1, i)
            d[i][j] = (a[i] & a[j]) ? 1 : inf;
        d[i][i] = 0;
    }
    int ans = inf;
    rep (k, 1, n) {
        re (i, 1, k) if (d[k][i] == 1) re (j, 1, i) if (d[k][j] == 1) {
            ans = std::min(ans, d[i][j] + 2);
        }
        rep (i, 1, n) re (j, 1, i)
            d[i][j] = std::min(d[i][j], (i < k ? d[k][i] : d[i][k]) + (j < k ? d[k][j] : d[j][k]));
    }
    if (ans >= inf)
        io << "-1\n";
    else
        (io - ans) daze; 
}
