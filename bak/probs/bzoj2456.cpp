#include <cstdio>
#include <cctype>

int rd() {
    char c;
    for (c = getchar(); !isdigit(c); c = getchar());
    int x = c - '0';
    for (c = getchar(); isdigit(c); c = getchar())
        x = x * 10 + (c - '0');
    return x;
}

int main() {
    int n, x, ans, cnt = 0, q;
    char stk[11], *t = stk;
    n = rd();
    while (n--) {
        x = rd();
        if (cnt) {
            if (ans == x)
                ++cnt;
            else
                --cnt;
        } else
            ans = x, cnt = 1;
    }
    while (ans) {
        q = ans / 10;
        *t++ = '0' + (ans - q * 10);
        ans = q;
    }
    while (t != stk)
        putchar(*--t);
    return 0;
}
