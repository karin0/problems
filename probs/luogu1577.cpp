#include <cstdio>
#include <cmath>
#define MAXN 100010
int n, k;
double len[MAXN];
bool check(double l) {
    int cnt = 0;
    for (int i = 1; i <= n; ++i)
        if ((cnt += (int) floor(len[i] / l)) >= k)
            return true;
    return false;
}

int main() {
    double sum = 0.0, lb = 0.0, ub, mid;
    scanf("%d%d", &n, &k);
    for (register int i = 1; i <= n; ++i) {
        scanf("%lf", len + i);
        sum += len[i];
    }
    ub = sum / k + 1;
    while (ub - lb > 0.003) { // Checking [lb, ub)
        mid = (lb + ub) / 2;
        if (check(mid)) lb = mid;
        else ub = mid;
    }
    printf("%.2lf\n", lb);

    return 0;
}
