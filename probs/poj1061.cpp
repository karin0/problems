/*
POJ 1061
AC
数论;扩展欧几里得算法;同余方程
*/
#include <cstdio>
using namespace std;

typedef long long LL;

LL gcd(LL a, LL b) {
    return b==0 ? a : gcd(b, a%b);
}

void EXTGCD(LL a, LL b, LL& xx, LL& yy) {
    if (b==0) {
        xx=1;
        yy=0;
    } else {
        EXTGCD(b, a%b, yy, xx);
        yy -= a / b * xx;
    }
}

LL x, y, m, n, l;
LL g, a, b, c;
LL k, t, ans;
int main() {
    scanf("%lld%lld%lld%lld%lld", &x, &y, &m, &n, &l);
    // x + mt = y + nt (mod L)
    // (n-m)t = x - y (mod L)
    // Lk + (n-m)t = x - y
    a=l;
    b=n-m;
    c=x-y;
    g=gcd(a, b);
    if (c%g==0) { // 有解的充要条件
        a/=g;
        b/=g;
        c/=g;
        EXTGCD(a, b, k, t); // Solve k, t for ak+bt=1
        t*=c; // Make t for ak+bt=c
        ans = (t%a+a)%a; // ?通解 y = c*(y0-ak)
        printf("%lld\n", ans);
    } else {
        printf("Impossible\n");
    }
    return 0;
}
