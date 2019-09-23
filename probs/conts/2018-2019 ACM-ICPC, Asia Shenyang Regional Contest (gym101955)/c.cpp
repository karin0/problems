#include <akari>

IO<1000000, 1000000> io;

cint N = 100002;

int m;
inline int fac(int n) {
    int ans = 1;
    rep (i, 2, n)
        ans = (ll)ans * i % m;
    return ans;
}

int main() {
    int T;
    io >> T;
    rep (ks, 1, T) {
        int n, k;
        io >> n >> k >> m;
        io << "Case #" << ks << ": ";
        if (k >= n)
            io << fac(n) daze;
        else
            io << fac(k) * (ll(n - 1) * (n - k) % m + 1) % m daze;
    }
}
