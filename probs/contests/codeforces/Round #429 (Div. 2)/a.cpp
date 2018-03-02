#include <cstdio>

const int MAXS = 105;

char s[MAXS];
int n, k, cnt[500];

int main() {
    scanf("%d%d%s", &n, &k, s);
    for (char *c = &s[0]; *c; ++c)
        if (++cnt[*c] > k) {
            printf("NO\n");
            return 0;
        }
    printf("YES\n");

    return 0;
}
