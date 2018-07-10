#include <cstdio>

const int p = 10007;
int a, b, k, n, m, comb[1003][1003];
void calc_comb() {
    static int i, j;
    comb[0][0] = 1;
    for (i = 1; i <= k; ++i) {
        comb[i][0] = 1;
        for (j = 1; j <= i; ++j)
            comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % p;
    }
}
int qpow(int h, int e) {
    static int res;
    for (res = 1, h %= p; e; e >>= 1, h = h * h % p)
        if (e & 1)
            res = res * h % p;
    return res;
}
int main() {
    scanf("%d%d%d%d%d", &a, &b, &k, &n, &m);
    calc_comb();
    printf("%d\n", comb[k][n] * qpow(a, n) % p * qpow(b, m) % p);

    return 0;
}
