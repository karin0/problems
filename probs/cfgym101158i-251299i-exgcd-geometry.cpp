#define I 1000000
#define O 1000000
#include <akari>

cint N = 100002;

int g;
void exgcd(int a, int b, int &x, int &y) {
    if (b) {
        exgcd(b, a % b, y, x);
        y -= x * (a / b);
    } else
        g = a, x = 1, y = 0;
}

int main() {
    int T;
    pio >> T;
    while (T--) {
        int xb, yb, x, y;
        pio >> xb >> yb;
        // (x, y)
        // S = (xb * y - yb * x) / 2
        exgcd(xb, yb, y, x);
        if (g <= 50000) {
            io << "3\n0 0\n";
            uio << std::abs(x) << ' ' << std::abs(y) << '\n';
            pio << xb << ' ' << yb << '\n';
        } else {
            io << "4\n0 0\n";
            pio << xb - 1 << ' ' << yb << '\n';
            pio << xb / g << ' ' << yb / g << '\n';
            pio << xb << ' ' << yb - 1 << '\n';
        }

    }
}
