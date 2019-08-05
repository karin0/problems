#include <cstdio>

int main() {
    long long n;
    int cnt = 0;
    scanf("%lld", &n);
    for (; n; n >>= 1, ++cnt);
    printf("%d\n", cnt);

    return 0;
}
