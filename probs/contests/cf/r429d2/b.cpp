#include <cstdio>

int n, x, s;
bool flag;
int main() {
    scanf("%d", &n);
    while (n--) {
        scanf("%d", &x);
        s = (s + x) & 1;
        if (s)
            flag = true;
    }
    printf(s ? "First\n" : (flag ? "First\n" : "Second\n"));

    return 0;
}
