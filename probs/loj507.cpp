#include <cstdio>
#include <algorithm>
#define MAXN 1000100
#define INF 99999999999999999

inline int read() {
    int data = 0;
    char ch = 0;
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9') {
        data = data * 10 + (ch - '0');
        ch = getchar();
    }
    return data;
}

int n, k, c[MAXN], v[MAXN];
long long 
     sv[MAXN],  // sv(i) = sum{v(k) | k from 1 to i}<F10><F10>
     mf[MAXN],  // mf(i) = max{f(k) | 0 < k <= i}
     f[MAXN],   // f(i)  = max{sum{v(k) | k from j + 1 to i} + max{f(k) | 0 < k <= j} | c(j) = c(i) and 0 < j < i}
                //       = max{sv(i) - sv(j - 1) + mf(j - 1) | c(j) = c(i) and 0 < j < i}
                //       = sv(i) + max{mf(j - 1) - sv(j - 1) | c(j) = c(i) and 0 < j < i}
     ms[MAXN];  // ms(i, c) = max{mf(j - 1) - sv(j - 1) | c(j) = c and 0 < j <= i}
                // 对每个 c 动态维护
int main() {
    scanf("%d%d", &n, &k);
    register int i;
    std::fill(ms + 1, ms + k + 1, -INF); // Init it for 不可估计的 values 
    for (i = 1; i <= n; ++i)
        c[i] = read();
    for (i = 1; i <= n; ++i) {
        v[i] = read();
        sv[i] = sv[i - 1] + v[i];
    }
    for (i = 1; i <= n; ++i) {
        f[i] = std::max(f[i], sv[i] + ms[c[i]]);
        mf[i] = std::max(mf[i - 1], f[i]);
        ms[c[i]] = std::max(ms[c[i]], mf[i - 1] - sv[i - 1]);
    }
    printf("%lld\n", mf[n]);
    return 0;
}
