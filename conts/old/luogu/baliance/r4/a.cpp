#include <cstdio>
#include <cctype>

const int MAXL = 100007;
char s[MAXL];
int main() {
    char *c = &s[0], ch = getchar();
    while (ch != '\n' && ch != '\r') {
        *(c++) = ch;
        ch = getchar();
    }
    *c = 0;
    bool flag = true;
    for (c = &s[0]; *c; ++c) {
        if (*c == '.')
            flag = true, putchar('.');
        else if (isalpha(*c)) {
            if (flag)
                putchar(toupper(*c)), flag = false;
            else
                putchar(tolower(*c));
        } else
            putchar(*c);
    }
    putchar('\n');

    return 0;
}
