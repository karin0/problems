#include <cstdio>
#define MAXN 100010
int n, k;
int len[MAXN];
bool check(int l) {
    int cnt = 0;
    for (int i = 1; i <= n; ++i)
        if ((cnt += len[i] / l) >= k)
            return true;
    return false;
}

int main() {
    int sum = 0, lb = 0, ub, mid;
    scanf("%d%d", &n, &k);
    for (register int i = 1; i <= n; ++i) {
        scanf("%d", len + i);
        sum += len[i];
    }
    ub = sum / k + 1;
    while (ub - lb > 1) { // Checking [lb, ub)
        mid = lb + ((ub - lb) >> 1);
        if (check(mid)) lb = mid;
        else ub = mid;
    }
    printf("%d\n", lb);

    return 0;
}
