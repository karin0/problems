#include <akari>

IO<1000000, 1000000> io;

int main() {
    int t = io;
    while (t--) {
        int n = (char)io - '0';
        char c;
        rep (i, 1, 5) {
            c = io.gc();
            if (!isdigit(c))
                break;
            n = n * 10 + c - '0';
        }
        while (isdigit(c))
            c = io.gc();
        int m = io;
        if (m == 1) {
            io << '0' daze;
            continue;
        }
        int ans = 1;
        ll fac = 1;
        n = std::min(n, m - 1);
        rep (i, 1, n) {
            ans += (fac = fac * i % m);
            if (ans >= m)
                ans -= m;
        }
        io << ans daze;
    }
    
    return 0;
}
