#include <cstdio>
#include <cstring>

const int MAXS = 15005;

char ss[MAXS], *s;
int num[MAXS], next[MAXS];
int main() {
    static int k, i, j, l, ans, len;
    scanf("%s%d", ss + 1, &k);
    len = strlen(ss + 1) - k - k;
    for (l = 1; l <= len; ++l) {
        s = ss + l - 1;
        next[1] = 0;
        num[1] = (1 < k) ? 0 : 1;
        for (i = 2; s[i]; ++i) {
            for (j = next[i - 1]; j && s[j + 1] != s[i]; j = next[j]);
            if (s[j + 1] == s[i])
                ++j;
            next[i] = j;
        }
        for (i = 1, j = 0; s[i]; ++i) {
            for (; j && s[j + 1] != s[i]; j = next[j]);
            if (s[j + 1] == s[i])
               ++j;
            // Or `j = next[i];` which seems faster
            while ((j << 1) >= i)
                j = next[j];
            if (j >= k)
                ++ans;
        }
    }
    printf("%d\n", ans);
    return 0;
}
