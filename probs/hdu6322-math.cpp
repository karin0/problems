#include <akari>

IO<1000000, 1000000> io;

int main() {
    int t, k;
    io >> t;
    while (t--) {
        io >> k;
        if (k == 1)
            io << '5' daze;
        else
            io << 5 + k daze;
    }
    
    return 0;
}
