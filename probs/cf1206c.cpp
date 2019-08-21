#include <akari>

IO<10, 100000> io;

cint N = 200002;

int a[N];
int main() {
    int n;
    io > n;
    if (n & 1) {
        io << "YES\n";
        rep (i, 1, n) {
            a[i] = i << 1;
            a[n + i] = a[i] - 1;
            if (i & 1)
                std::swap(a[i], a[n + i]);
        }
        n <<= 1;
        re (i, 1, n)
            (io - a[i]) << ' ';
        (io - a[n]) daze;
    } else
        io << "NO\n";

    
    return 0;
}
