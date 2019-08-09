#include <akari>
IO<1000000, 1000000> io;

char p[20];
int main() {
    int n;
    io >> n >> p;
    int k = 0;
    while (p[k])
        ++k;
    if (n < k) {
        puts("T_T");
        return 0;
    }
    io << p;
    for (int i = k; i < n; ++i)
        io.pc('0');
    io.pc('\n');
    return 0;
}