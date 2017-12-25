#include <cstdio>
#include <cstring>

const int MAXS = 1000005, mo = 1000000007;

char s[MAXS];
int num[MAXS], next[MAXS]; // num[] is not defined as the problem
int main() {
    int m, res, i, j, len;
    scanf("%d", &m);
    while (m--) {
        res = 1;
        scanf("%s", s + 1); // t is the pattern
        len = strlen(s + 1);
        num[1] = 1;
        for (i = 2; i <= len; ++i) {
            for (j = next[i - 1]; j != 0 && s[j + 1] != s[i]; j = next[j]);
            if (s[j + 1] == s[i])
                ++j;
            next[i] = j;
            num[i] = num[next[i]] + 1;
        }
        for (i = 1, j = 0; i <= len; ++i) {
            while (j != 0 && s[j + 1] != s[i])
                j = next[j];
            if (s[j + 1] == s[i])
                ++j;
            while ((j << 1) > i)
                j = next[j];
            res = (long long)res * (num[j] + 1) % mo;
        }
        printf("%d\n", res);
    }
    return 0;
}
