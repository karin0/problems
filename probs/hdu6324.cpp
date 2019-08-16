#include <akari>

IO<1000000, 1000000> io;

int main() {
    int t = io;
    while (t--) {
        int n = io, s = 0;
        rep (i, 1, n)
            s ^= int(io);
        re (i, 1, n) {
            int x;
            io >> x >> x;
        }
        io << (s ? 'Q' : 'D') daze;
    }
    
    return 0;
}
