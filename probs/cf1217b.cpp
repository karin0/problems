#include <akari>

IO<1000000, 1000000> io;

inline int udiv(int a, int b) {
    std::div_t x = std::div(a, b);
    return x.rem ? x.quot + 1 : x.quot;
}
inline int solve() {
    int n, x, d, h;
    io >> n >> x;
    int k = INT_MIN, maxd = INT_MIN;
    rep (i, 1, n) {
        io >> d >> h;
        k = std::max(k, d - h);
        maxd = std::max(maxd, d);
    }
    if (maxd >= x)
        return 1;
    if (k <= 0)
        return -1;
    return udiv(x - maxd, k) + 1;
}

int main() {
    int T;
    io >> T;
    while (T--)
        io << solve() daze;
}
