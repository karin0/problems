#include <akari>

IO<1000000, 1000000> io;

cint N = 100002;

int a[10];
int main() {
    int n = 4, s = 0;
    rep (i, 1, n) {
        io >> a[i];
        s += a[i];
    }
    if (s & 1) {
        io << "NO\n";
        return 0;
    }
    s >>= 1;
    rep (i, 1, n) {
        if (a[i] == s) {
            io << "YES\n";
            return 0;
        }
        re (j, 1, i)
            if (a[i] + a[j] == s) {
                io << "YES\n";
                return 0;
            }
    }
    io << "NO\n";
}
