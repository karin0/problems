#include <cstdio>

int t, a, b;
char tmp[4], proc[] = {'v', '<', '^', '>'};
inline int num(char c) {
    for (int i = 0; i < 4; ++i)
        if (proc[i] == c)
            return i;
    return 4;
}
int main() {
    scanf("%s", tmp);
    a = num(tmp[0]);
    scanf("%s", tmp);
    b = num(tmp[0]);
    scanf("%d", &t);
    t %= 4;
    if ((a + t) % 4 == b)
        if ((a - t + 400) % 4 == b)
            printf("undefined\n");
        else
            printf("cw\n");
    else if ((a - t + 400) % 4 == b)
        printf("ccw\n");
    else
        printf("undefined\n");

    return 0;
}
