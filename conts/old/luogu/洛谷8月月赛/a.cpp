#include <cstdio>
#include <cmath>
#include <map>
typedef long long LL;
const LL MOD = 998244353;
std::map<LL, LL> mem;
inline LL f(LL x) {
    LL res = 0;
    LL sqr = round(sqrt(x));
    LL t1, t2;
    bool flag = false;
    for (LL i = 2; i < sqr; ++i)
        if (!(x % i)) {
            printf("[%lld * %lld = %lld]\n", i, x / i, x);
            if (flag)
                res += 1;
            else {
                flag = true;
                t2 = f(x / i);
                res += 1 + t2;
            }
        }
    printf("[f(%lld) = %lld]\n", x, res);
    return res;
}


int main() {
    int q;
    LL x;
    scanf("%d", &q);
    while (q--) {
        scanf("%lld", &x);
        printf("%lld\n", f(x));
    }

    return 0;
}
