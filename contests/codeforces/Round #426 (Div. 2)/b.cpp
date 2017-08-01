#include <cstdio>
const int MAXN = 1e7;

bool opened[100];
int n, k, ocnt = 0, d; // opened count
char order[MAXN];

int last[100], lcnt = 0;

int main() {
    int i;
    scanf("%d%d", &n, &k);
    scanf("%s", order + 1);
    if (k == 26) {
        printf("NO\n");
        return 0;
    }
    for (i = n; i >= 1 && lcnt < 26; --i) {
        d = order[i] - 'A';
        if (!last[d]) {
            last[d] = i;
            ++lcnt;
        }
    }
    for (i = 1; i <= n; ++i) {
        d = order[i] - 'A';
        if (opened[d]) {
            if (i == last[d]) {
                // opened[d] = false;
                --ocnt;
            }
        } else {
            opened[d] = true;
            if (++ocnt > k) {
                printf("YES\n");
                return 0;
            }
            if (i == last[d]) {
                // opened[d] = false;
                --ocnt;
            } // 特判 first[d] == last[d]
        }
    }
    printf("NO\n");
    return 0;
}
