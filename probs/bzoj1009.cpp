#include <cstdio>
#include <cstring>

const int MAXM = 20;

int n, m, mo;
struct Matrix {
    int v[MAXM][MAXM];
    int &operator () (const int i, const int j) {
        return v[i][j];
    }
    Matrix operator * (Matrix &b) {
        static int i, j, k;
        Matrix res;
        for (i = 0; i < m; ++i) {
            for (j = 0; j < m; ++j) {
                res(i, j) = 0;
                for (k = 0; k < m; ++k)
                    (res(i, j) += v[i][k] * b(k, j)) %= mo;
            }
        }
        return res;
    }
};
void qpow(Matrix a, int k, Matrix &res) {
    for (res = a, --k; k; k >>= 1, a = a * a)
        if (k & 1)
            res = res * a;
}


char s[MAXM + 1];
int main() {
    static int i, j, fail[MAXM + 1], ans;
    scanf("%d%d%d%s", &n, &m, &mo, s + 1);

    fail[1] = 0;
    for (i = 2; i <= m; ++i) {
        for (j = fail[i - 1]; j != 0 && s[j + 1] != s[i]; j = fail[j]);
        fail[i] = (s[j + 1] == s[i]) ? j + 1 : 0;
    }
    static Matrix mat, res;
    static char c;
    for (i = 0; i < m; ++i) {
        for (c = '0'; c <= '9'; ++c) {
            for (j = i; j && s[j + 1] != c; j = fail[j]);
            if (s[j + 1] == c)
                ++j;
            ++mat(j, i); // 影响 f(? - 1, i) 对 f(?, j) 的贡献
        }
    };
    qpow(mat, n, res);
    for (i = 0; i < m; ++i)
        (ans += res(i, 0)) %= mo;
    printf("%d\n", ans);
    
    return 0;
}
