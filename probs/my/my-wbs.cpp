#include <cstdio>
#include <algorithm>

typedef long long ll;
const int mo = 998244353;
struct Matrix {
    static const int n = 2;
    int v[n][n];
    int &operator () (const int i, const int j) {
        return v[i][j];
    }
    Matrix operator * (Matrix &b) {
        Matrix res;
        static int i, j, k;
        for (i = 0; i < n; ++i) {
            for (j = 0; j < n; ++j) {
                res(i, j) = 0;
                for (k = 0; k < n; ++k) 
                    res(i, j) = (res(i, j) + (ll)v[i][k] * b(k, j) % mo) % mo;
            }
        }
        return res;
    }
};
void pow(Matrix& a, int k, Matrix& res) {
    for (res = a, --k; k; k >>= 1, a = a * a)
        if (k & 1)
            res = res * a;
}

int main() {
    static int n, a1, a2;
    static Matrix b, res;
    scanf("%d%d%d%d%d", &n, &a1, &a2, &b(1, 1), &b(1, 0));
    if (n <= 2) {
        printf("%d\n", std::max(a1, a2) % mo);
        return 0;
    }
    b(0, 0) = 0;
    b(0, 1) = 1;
    pow(b, n - 2, res);
    printf("%d\n", (int) (((ll)res(1, 0) * a1 % mo + (ll)res(1, 1) * a2 % mo) % mo));
    return 0;
}
