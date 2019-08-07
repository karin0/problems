#include <cstdio>

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}
int main() {
    int a, b;
    while (scanf("%d%d", &a, &b) == 2)
        printf("%d\n", a / gcd(a, b) * b);
}