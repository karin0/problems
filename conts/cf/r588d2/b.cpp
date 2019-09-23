#include <akari>

IO<1000000, 1000000> io;

cint N = 200005;

char a[N];
int main() {
    int n, k;
    io >> n >> k >> (a + 1);
    if (n == 1) {
        if (k) {
            io << "0\n";
            return 0;
        }
    } else if (k) {
        if (a[1] != '1') {
            a[1] = '1';
            --k;
        }
        for (int i = 2; k && i <= n; ++i) {
            if (a[i] != '0') {
                a[i] = '0';
                --k;
            }
        }
    }
    io << (a + 1) daze;
}
