#include <akari>

IO<1000000, 1000000> io;

cint N = 40000002;

int a[N], next[N], prev[N];
int main() {
    int T;
    io >> T;
    while (T--) {
        int n, m, q;
        io >> n >> m >> q;

        rep (i, 1, n) {
            next[i] = i + 1;
            prev[i] = i - 1;
            a[i] = 0;
        }
        next[n] = prev[1] = 0;

        rep (i, 1, n) {

        }


    }
}
