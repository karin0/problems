#include <cstdio>

typedef long long ll;
const int MAXK = 12, MAXW = 14;
const ll MOD = 1e9 + 7;

int r, w;
ll n, co[MAXK][MAXK];

inline void make_comb() {
    co[0][0] = 1; // ***
    for (int i = 1; i <= r; ++i) {
        co[i][0] = 1; // ***
        for (int j = 1; j <= i; ++j) {
            co[i][j] = co[i - 1][j - 1] + co[i - 1][j];
            if (co[i][j] > MOD)
                co[i][j] -= MOD;
        }
    }
}

struct Matrix {
    ll a[MAXW][MAXW]; // (k + 2) * (k + 2)
};
Matrix operator * (const Matrix &a, const Matrix &b) {
    Matrix c;
    for (int i = 1; i <= w; ++i) {
        for (int j = 1; j <= w; ++j) {
            c.a[i][j] = 0;
            for (int k = 1; k <= w; ++k) {
                c.a[i][j] = (c.a[i][j] + a.a[i][k] * b.a[k][j]) % MOD; // ***
            }
        }
    }
    return c;
}

inline void qpow(Matrix &a, ll p, Matrix &res) {
    res = a;
    --p;
    for (; p; p >>= 1, a = a * a)
        if (p & 1)
            res = res * a;
}

// f(n+1) = 2*f(n) + (n+1)^k - n^k
int main() {
    Matrix a, res;
    int i, j;
    ll ans = 0;
    scanf("%lld%d", &n, &r);
    if (n == 1) {
        puts("1\n");
        return 0;
    }
    w = r + 2;
    make_comb();
    for (i = 1; i <= w; ++i)
        for (j = 1; j <= w; ++j)
            a.a[i][j] = 0;
    a.a[1][1] = 2;
    for (i = 0; i <= r; ++i)
        a.a[1][r - i + 2] = co[r][i];
    a.a[1][2] -= 1;
    for (i = 0; i <= r; ++i)
        for (j = 0; j <= i; ++j)
            a.a[r - i + 2][r - j + 2] = co[i][j];
    qpow(a, n - 1, res);
    for (i = 1; i <= w; ++i) { 
        ans += res.a[1][i];
        if (ans > MOD)
            ans -= MOD;
    }
    printf("%lld\n", ans);
    
    return 0;
}
