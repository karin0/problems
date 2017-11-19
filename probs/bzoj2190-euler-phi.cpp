#include <cstdio>

const int MAXN = 40005;

bool np[MAXN];
int phi[MAXN], pri[MAXN], pcnt;
inline void euler(int n) {
    static int i, j;
    static long long v;
    np[0] = np[1] = true;
    phi[1] = 1;
    for (i = 2; i <= n; ++i) {
        if (!np[i])
            pri[++pcnt] = i, phi[i] = i - 1;
        for (j = 1; j <= pcnt; ++j) {
            v = (long long)pri[j] * i;
            if (v > n)
                break;
            np[v] = true;
            if (i % pri[j] == 0) {
                phi[v] = phi[i] * pri[j];
                break;
            } else
                phi[v] = phi[i] * (pri[j] - 1);
        }
    }

}

int main() {
    static int n, ans, i;
    scanf("%d", &n); // ans = 1 + sum{phi(i), i = 1 to n - 1}
    --n;
    euler(n);
    for (i = 1; i <= n; ++i)
        ans += phi[i];
    printf("%d\n", 1 + (ans << 1));
    
    return 0;
}
