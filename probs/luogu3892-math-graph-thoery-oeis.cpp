#include <bits/stdc++.h>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))
#ifdef AKARI
    #define ccc(x) std::cerr << #x " = " << (x) << "  "
    #define ccf(x) std::cerr << #x " = " << (x) << std::endl
    #define cccc(...) fprintf(stderr, __VA_ARGS__)
#else
    #define ccc(x)
    #define ccf(x)
    #define cccc(...)
#endif
typedef long long ll;

const int mo = 998244353, N = 1000007, b1 = 100000, b2 = 998999998, b3 = 1000000000;
const ll inv2 = 499122177ll;
int mck2(const int x) {
    return x < 0 ? x + mo : x;
}
int mck3(const int x) {
    return x < 0 ? x + mo : (x >= mo ? x - mo : x);
}
int a1[N], a2[N];
bool inited;
void init1() {
    a1[1] = 1; a1[2] = 3;
    a2[1] = 1; a2[2] = 4;
    int i; rep (i, 3, b1) {
        a1[i] = mck3(((ll)i * a1[i - 1] - (ll)(i - 1) * a1[i - 2] + 1) % mo);
        a2[i] = ((ll)i * a2[i - 1] + i) % mo;
    }
}
void init2() {
    a1[0] = 756864412; a1[1] = 412436192;
    a2[0] = 653816132; a2[1] = 453961452;
    int i; rep (i, b2 + 2, b3) {
        a1[i - b2] = mck3(((ll)i * a1[i - 1 - b2] - (ll)(i - 1) * a1[i - 2 - b2] + 1) % mo);
        a2[i - b2] = ((ll)i * a2[i - 1 - b2] + i) % mo;
    }
}
int solve1(const int n) {
    if (n <= 3)
        return 0;
    if (!inited)
        init1(), inited = true;
    return mck2(mck2(a1[n] - ((ll)n * (n + 1) % mo * inv2 % mo)) * inv2 % mo - a2[n - 2]);
}
int solve2(const int n) {
    if (!inited)
        init2(), inited = true;
    return mck2(mck2(a1[n - b2] - ((ll)n * (n + 1) % mo * inv2 % mo)) * inv2 % mo - a2[n - 2 - b2]);
}
int solve(const int n) {
    if (n <= b1)
        return solve1(n);
    else
        return solve2(n);
}
int main() {
    static int ks, n;
    scanf("%d", &ks);
    while (ks--) {
        scanf("%d", &n);
        printf("%d\n", solve(n));
    }
    return 0;
}

