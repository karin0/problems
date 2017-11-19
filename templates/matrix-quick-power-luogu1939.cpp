#include <cstdio>

typedef long long ll;
const int MOD = 1000000007, m = 3;
struct Mat {
    int v[m + 1][m + 1];
    inline int *operator [] (const int i) {
        return v[i];
    }
};
inline Mat operator * (const Mat &a, const Mat &b) {
    Mat res;
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= m; ++j) {
            res[i][j] = 0;
            for (int k = 1; k <= m; ++k) {
                res[i][j] = (res[i][j] + (ll)a[i][k] * b[k][j] % MOD) % MOD;
            }
        }
    }
    return res;
}
void qpow(Mat a, int k, Mat &res) { // do not use 引用 for a
    res = a;
    --k;
    for (; k; k >>= 1, a = a * a)
        if (k & 1)
            res = res * a;
}

int main() {
    static int n, t, ans, i;
    static Mat z, res;
    scanf("%d", &t);
    z[1][1] = z[1][3] = z[2][1] = z[2][2] = z[2][3] = z[3][1] = z[3][2] = 1;
    z[1][2] = 0;
    z[3][3] = 2;
    while (t--) {
        scanf("%d", &n);
        if (n <= 3) {
            puts("1");
            continue;
        }
        qpow(z, (n - 1) / 3, res);
        ans = 0;
        n %= 3;
        if (n == 0)
            n = 3;
        for (i = 1; i <= m; ++i)
            ans = (ans + res[n][i]) % MOD;
        printf("%d\n", ans);
    }
    
    return 0;
}
