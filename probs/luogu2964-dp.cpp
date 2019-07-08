#include <akari>

IO<1000000, 10> io;

cint N = 2002;

inline void upd(int &x, cint v) {
    if (v > x) x = v;
}

int f[N][N], s[N];
int main() {
    int n = io; // h = (n + 1) >> 1;
    per (i, n, 1)
        io >> s[i];
    rep (i, 2, n)
        s[i] += s[i - 1];

    /*
    rep (i, 1, n) {
        int *fij = f[i], l = (i < n) ? h : 1, k = 0, si = s[i], j;
        for (j = 1; j <= l && k <= i; ++j) {
            ++fij;
            *fij = *(fij - 1);
            if (++k <= i) upd(*fij, si - f[i - k][k]);
            if (++k <= i) upd(*fij, si - f[i - k][k]);
        }
        if (j <= l) {
            int t = *fij;
            do {
                *++fij = t;
                ++j;
            } while (j <= l);
        }
    }
    */
    rep (i, 1, n) for (int k = 0, j = 1; j <= n; ++j) {
        f[i][j] = f[i][j - 1];
        if (++k <= i) upd(f[i][j], s[i] - f[i - k][k]);
        if (++k <= i) upd(f[i][j], s[i] - f[i - k][k]);
    }

    io << f[n][1] daze;

    return 0;
}
