#include <cstdio>
#include <algorithm>

const int MAXN = 1e7 + 5;

int n, a[MAXN];
double ans;

int main() {
    int pa, pb, pc, i;
    scanf("%d%d%d%d%d", &n, &pa, &pb, &pc, a + 1);
    for (i = 2; i <= n; ++i)
        a[i] = ((long long)a[i - 1] * pa + pb) % 100000001;
    for (i = 1; i <= n; ++i)
        a[i] = a[i] % pc + 1;

    a[0] = a[n];
    for (i = 1; i <= n; ++i)
        ans += (double)std::min(a[i - 1], a[i]) / ((long long)a[i - 1] * a[i]);
    
    printf("%.3lf", ans);

    return 0;
}
