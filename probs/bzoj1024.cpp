#include <cstdio>
#include <algorithm>
using std::min;
using std::max;
double dfs(double x, double y, int k) { // Cut an x * y cake into k parts, min of max(ratio(x0, y0)).
    if (k == 1) {
        return (x > y) ? (double)x / y : (double)y / x;
    }
    double r = 100000.0, x1, y1;
    for (int k1 = 1; k1 <= k / 2; ++k1) {
        x1 = (double)x / k * k1;
        y1 = (double)y / k * k1;
        r = min(r, min(max(dfs(x1, y, k1), dfs(x - x1, y, k - k1)), max(dfs(x, y1, k1), dfs(x, y - y1, k - k1))));
    }
    return r;
}

int main() {
    int x, y, n;
    scanf("%d%d%d", &x, &y, &n);
    printf("%.6f", dfs(x, y, n));
    return 0;
}
