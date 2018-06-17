#include <cstdio>

const int mo = 10007;
int main() {
    static char s[505], *p;
    static int n;
    scanf("%s", s);
    for (p = s; *p; ++p)
        n = (n * 10 + (*p - '0')) % mo;
    printf("%d\n", n * (n + 1) % mo * (n + 2) % mo * 1668 % mo);
    return 0;
}
