#include <akari>

IO<1000000, 100> io;

cint N = 100002;

int f_[N + N];
int main() {
    int n, s = 0, c0 = 0, c1 = 0, ans = 0, *f = f_ + N;
    io >> n;
    std::fill(f - n, f + n + 1, -1);
    f[0] = 0;
    rep (i, 1, n) {
        if ((char)io == '1')
            ++c1, ++s;
        else
            ++c0, --s;
        if (f[s] >= 0)
            ans = std::max(ans, i - f[s]);
        else
            f[s] = i;
    }
    io << ans << ' ' << 2 * std::min(c0, c1) daze;

    return 0;
}
