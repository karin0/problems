#include <cstdio>


int main() {
    int x, t;
    scanf("%d%d", &x, &t);
    printf("%d\n", x - (t >= x ? x : t));

    return 0;
}
