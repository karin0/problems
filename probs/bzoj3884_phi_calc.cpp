#include <cstdio>

int qpow(int x, int p, int mo) {
    static int res;
    for (res = 1; p; p >>= 1, x = (long long)x * x % mo) // use ll!
        if (p & 1)
            res = (long long)res * x % mo;
    return res; // int
}

inline int phi(int x) {
    static int i, res;
    for (res = x, i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
            res -= res / i;
            while (x % i == 0)
                x /= i;
        }
    }
    if (x > 1)
        return res - res / x;
    return res;
}
// int mem[10000005]; // use of mem makes it slower.
inline int f(int x) {
    // if (mem[x] > 0)
    //    return mem[x] - 1;
    if (x == 1)
        return 0;
    int t = phi(x); // No static!
    // return (mem[x] = qpow(2, f(t) + t, x) + 1) - 1;
    return qpow(2, f(t) + t, x);
}

int main() {
    static int t, p, ks;
    // mem[1] = 1;
    scanf("%d", &t);
    for (ks = 0; ks < t; ++ks) {
        scanf("%d", &p);
        printf("%d\n", f(p));
    }
    return 0;
}
