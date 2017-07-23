#include <cstdio>
#define MAXS 9999999
int n, ord;
char s[MAXS];
int main() {
    scanf("%d%s", &n, s);
    n %= 26;
    for (char *p = &s[0]; *p; ++p) {
        ord = (*p - 'a') + n;
        while (ord > 'z' - 'a')
            ord -= 26;
        printf("%c", 'a' + ord);
    }
    printf("\n");
    return 0;
}
