#include <akari>

IO<1000000, 1000000> io;

cint N = 100002;

int a[N];
int main() {
    int t = io;
    while (t--) {
        int n = io, sum = 0, cnt = 0;
        rep (i, 1, n)
            io >> a[i];
        bool fail = false;
        rep (i, 1, n) {
            char b = io;
            if (fail)
                continue;
            if (b == '0' || (b == '1' && a[i] == 1)) {
                sum ^= a[i];
                continue;
            }
            if (++cnt > 1) {
                fail = true;
                continue;
            }
            if (a[i] & 1) {
                if (b == '2')
                    fail = true;
            } else if (b == '1')
                sum ^= 1;
        }
        if (fail)
            io << "Bob\n";
        else if (cnt)
            io << (sum ? "Bob\n" : "Alice\n");
        else
            io << (sum ? "Alice\n" : "Bob\n");
    }

    return 0;
}
