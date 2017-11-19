#include <cstdio>
typedef long long LL;

LL qpow(LL x, LL p, LL m) {
    LL res = 1;
    for (; p; p >>= 1, x = x * x % m)
        if (p & 1)
            res = (res * x) % m;
    return res;
}

int main() {
    LL x, p, m;
    scanf("%lld%lld%lld", &x, &p, &m);
    printf("%lld^%lld mod %lld=%lld", x, p, m, qpow(x, p, m));
    return 0;
}
