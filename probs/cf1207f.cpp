#include <akari>

IO<1000000, 1000000> io;

cint n = 500000, s = 707;

int a[n + 1], b[s + 2][s];
int main() {
    int m;
    io > m;
    while (m--) {
        int t, x, y;
        io > t > x;
        if (t == 1) {
            io >> y;
            a[x] += y;
            rep (i, 1, s)
                b[i][x % i] += y;
        } else {
            io > y;
            if (x <= s)
                io << b[x][y] daze;
            else {
                int ans = 0;
                for (int i = y; i <= n; i += x)
                    ans += a[i];
                io << ans daze;
            }
        }
    }
    return 0;
}
