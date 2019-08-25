#include <cstdio>
#include <cstring>

char p[20];
int main() {
    int n;
    scanf("%d%s", &n, p);
    int k = strlen(p);
    if (n < k) {
        puts("T_T");
        return 0;
    }
    printf("%s", p);
    for (int i = k + 1; i <= n; ++i)
        putchar('0');
    putchar('\n');
    return 0;
}