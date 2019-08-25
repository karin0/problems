#include <cstdio>
#include <cstring>

const int MAXN = 200010;

char s[MAXN];
int n, pcnt, ma[MAXN];
int sta[MAXN], top = 0;

int main() {
    freopen("unknown.in", "r", stdin);
    freopen("unknown.out", "w", stdout);
    int i, x, v = 1;
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (i = 1; i <= n; ++i) {
        if (s[i] == '(')
            sta[++top] = i;
        else if (s[i] == ')') {
            x = sta[top--];
            ma[x] = i;
            ma[i] = x;
        }
    }
    x = 1;
    while (x <= n) {
        // printf("%d %d %c\n", x, v, s[x]);
        if (s[x] == '(' || s[x] == ')')
            x = ma[x], v = -v;
        else
            putchar(s[x]);
        x += v;
    }
    putchar('\n');
    
    return 0;
}
