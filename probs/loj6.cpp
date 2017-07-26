#include <cstdio>
const int MAXN = 105;
int ans[MAXN];
int n;
int main() {
    printf("get_num\n");
    fflush(stdout);
    scanf("%d", &n);
    int lb, ub, mid, ret, i;
    for (i = 0; i < n; ++i) {
        lb = 0, ub = 1000000;
        while (true) {
            if (lb == ub) {
                ans[i] = lb;
                break;
            }
            mid = (lb + ub) >> 1;
            printf("guess %d %d\n", i, mid);
            fflush(stdout);
            scanf("%d", &ret);
            if (ret == 1)
                ub = mid - 1;
            else if (ret == -1)
                lb = mid + 1;
            else {
                ans[i] = mid;
                break;
            }
        }
    }
    printf("submit ");
    for (i = 0; i < n; ++i) {
        printf("%d ", ans[i]);
    }
    printf("\n");
    fflush(stdout);
    return 0;
}
