#include <akari>

IO<100000, 100000> io;

cint N = 102;

int a[N], b[N];
int main() {
    int a[] = {0, 0};
    rep (i, 0, 1) {
        int n, t;
        io > n;
        while (n--) {
            io > t;
            a[i] = std::max(a[i], t);
        }
    }
    (((io - a[0]) << ' ') - a[1]) << '\n';

    
    return 0;
}
