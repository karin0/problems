#include <akari>

IO<1000000, 10> io;

cint N = 10002;

int a[N];
int main() {
    int n, k;
    io >> n >> k;
    rep (i, 1, n)
        io >> a[i];
    std::sort(a + 1, a + n + 1);
    int m = std::unique(a + 1, a + n + 1) - a - 1;
    if (k > m)
        io << "NO RESULT\n";
    else
        io << a[k] daze;
    return 0;
}
