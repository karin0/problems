#include <akari>

IO<1000000, 1000000> io;

cint N = 100002;

ll s[N];
int main() {
    int T;
    io >> T;
    while (T--) {
        int n;
        io >> n;
        rep (i, 2, n)
            s[i] = (s[i - 1] << 1) - s[i - 2] + int(io);
        ll ans = 0;
        io << '0';
        rep (i, 2, n)
            io << ' ' << 
                (ans += s[n] - s[i >> 1] - s[n - (i >> 1)]);
        io << '\n';
    }
}