#include <akari>

IO<1000000, 1000000> io;

cint N = 102;

int a[N];
int main() {
    int n;
    io > n;
    int m = n << 1, ans = 0;
    rep (i, 1, m)
        io > a[i];
    for (int i = 1, j; i <= m; i += 2) {
        for (j = i + 1; a[i] != a[j]; ++j);
        ans += j - i;
        for (; j > i; a[j] = a[j - 1], --j);
    }
    (io < ans - n) daze;

    return 0;
}
