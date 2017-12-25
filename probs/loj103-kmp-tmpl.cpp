#include <cstdio>
#include <cstring>

const int MAXS = 1000005;

void get_next(char *s, int *next, int len) {
    static int i, j;
    next[1] = 0;
    for (i = 2; i <= len; ++i) {
        for (j = next[i - 1]; j != 0 && s[j + 1] != s[i]; j = next[j]);
        next[i] = (s[j + 1] == s[i]) ? j + 1 : 0;
    }
}

int kmp(char *s, char *pat) {
    static int next[MAXS], ls, lp, res, i, j;
    ls = strlen(s + 1), lp = strlen(pat + 1); // + 1
    get_next(pat, next, lp);
    res = 0;
    for (i = 1, j = 0; i <= ls; ++i) {
        while (j != 0 && pat[j + 1] != s[i])
            j = next[j];
        if (pat[j + 1] == s[i])
            ++j;
        if (j == lp)
            ++res, j = next[j];
    }
    return res;
}

int main() {
    static char s[MAXS], t[MAXS];
    scanf("%s%s", s + 1, t + 1); // t is the pattern
    printf("%d\n", kmp(s, t));
    return 0;
}
