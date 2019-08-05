#include <cstdio>

const int MAXM = 1003;

int n, m, a[MAXM], cnt[MAXM];

int main() {
    int i, j, k;
    bool flag[3];
    scanf("%d%d", &n, &m);
    k = 3 * m + 1;
    while (k--) {
        scanf("%d", &i);
        ++a[i];
    }
    flag[0] = false;
    for (i = 1; i <= n; ++i) {
        ++a[i];
        flag[1] = false;
        for (j = 1; j <= n; ++j)
            if (a[j] >= 2) {
                a[j] -= 2;
                flag[2] = true;
                for (k = 1; k <= n; ++k)
                    cnt[k] = a[k];
                a[j] += 2;
                for (k = 1; k <= n - 2; ++k)
                    if (cnt[k]) {
                        cnt[k] %= 3;
                        if (cnt[k + 1] >= cnt[k] && cnt[k + 2] >= cnt[k]) {
                            cnt[k + 1] -= cnt[k];
                            cnt[k + 2] -= cnt[k];
                            // cnt[k] = 0;
                        } else {
                            flag[2] = false;
                            break;
                        }
                    }
                cnt[n - 1] %= 3;
                cnt[n] %= 3; // ***
                if (flag[2] && cnt[n - 1] == 0 && cnt[n] == 0) {
                    flag[1] = true;
                    break;
                }
            }
        --a[i];
        if (flag[1]) {
            if (flag[0]) {
                printf(" %d", i);
            } else {
                printf("%d", i);
                flag[0] = true;
            }
        }
    }
    puts(flag[0] ? "\n" : "NO\n");
    
    return 0;
}
