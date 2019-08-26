#include <random>
#include <cstdio>

int n, l;
double x[12], y[12], r;
double sq(const double a) {
    return a * a;
}
int main() {
    static int i, ts = 100000;
    scanf("%d%d", &n, &l);
    for (i = 1; i <= n; ++i)
        scanf("%lf%lf", &x[i], &y[i]);
    r = (double)l / n;
    r *= r;
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_real_distribution<double> d(0, l);
    while (ts--) {
        static double xx, yy;
        static bool succ;
        xx = d(g);
        yy = d(g);
        succ = true;
        for (i = 1; i <= n; ++i) {
            if (sq(xx - x[i]) + sq(yy - y[i]) <= r) {
                succ = false;
                break;
            }
        }
        if (succ) {
            printf("%f %f\n", xx, yy);
            return 0;
        }
    }
    puts("GG");
    return 0;
}
