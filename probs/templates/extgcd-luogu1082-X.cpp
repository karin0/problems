#include <cstdio>

int g;
void extgcd(int a, int b, int &x, int &y) {
    if (b == 0)
        g = a, x = 1, y = 0;
    else
        extgcd(b, a % b, y, x), y -= x * (a / b);
}

void extgcd(int a, int b, int &x, int &y) {
    if (b == 0)
        g = a, x = 1, y = 0;
    else
        extgcd(b, a % b, y, x), y -= x * (a / b);
}
int main() {
    static int a, b, x, y;
    scanf("%d%d", &a, &b);
    // a * x - b * y = 1
    // Assuming gcd(a, b) = 1, or solution does not exist.
    extgcd(a, b, x, y);
    printf("%d\n", ((x % b) + b) % b);
    return 0;
}
    if (b == 0)
        g = a, x = 1, y = 0;
    else
        extgcd(b, a % b, y, x), y -= x * (a / b);
}

int main() {
    static int a, b, x, y;
    scanf("%d%d", &a, &b);
    // a * x - b * y = 1
    // Assuming gcd(a, b) = 1, or solution does not exist.
    extgcd(a, b, x, y);
    printf("%d\n", ((x % b) + b) % b);
    return 0;
}
