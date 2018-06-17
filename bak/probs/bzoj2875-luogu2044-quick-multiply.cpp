#include <cstdio>
#include <cstring>

typedef long long ll;
const int MAXN = 105;

ll mo;

ll qmul(ll a, ll b) {
    static ll res;
    for (res = 0; b; b >>= 1, (a <<= 1) %= mo)
        if (b & 1) (res += a) %= mo;
    return res;
}

struct Matrix { // n * n
    static const int n = 2;
    ll v[n][n];
    ll &operator () (const int i, const int j) {
        return v[i][j];
    }
    Matrix operator * (Matrix &b) {
        Matrix res;
        static int i, j, k;
        for (i = 0; i < n; ++i) {
            for (j = 0; j < n; ++j) {
                res(i, j) = 0;
                for (k = 0; k < n; ++k) 
                    (res(i, j) += qmul(v[i][k], b(k, j))) %= mo;
            }
        }
        return res;
    }
};
void qpow(Matrix& a, ll k, Matrix& res) {
    for (res = a, --k; k; k >>= 1, a = a * a)
        if (k & 1)
            res = res * a;
}


int main() {
    static ll k, b, a0, n, g, ans;
    scanf("%lld%lld%lld%lld%lld%lld", &mo, &k, &b, &a0, &n, &g);
    Matrix mat, res;
    mat(0, 0) = k % mo;
    mat(0, 1) = b % mo;
    mat(1, 0) = 0;
    mat(1, 1) = 1;
    qpow(mat, n, res);
    ans = (qmul(res(0, 0), a0 % mo) + res(0, 1)) % mo;
    printf("%lld\n", ans % g);
    return 0;
}
