#include <cstdio>
#include <cstring>

const int MAXN = 1e5 + 10;

int len;
char s[MAXN];

int main() {
    scanf("%s", s + 1);
    for (char* c = &s[1]; *c; ++c)
        if ((c - s) & 1)
            putchar(*c);
    putchar('\n');

    return 0;
}
