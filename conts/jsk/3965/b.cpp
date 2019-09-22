#include <cstdio>
#include <cstring>

char s[100004];
int main() {
    scanf("%s", s);
    int ans = 0;
    for (int i = 0, j = strlen(s) - 1; i < j; ++i, --j)
        if (s[i] != s[j])
            ++ans;
    printf("%d\n", ans);
}