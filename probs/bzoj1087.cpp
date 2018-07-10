#include <cstdio>

const int MAXS = 102;
int n, m;
int st[MAXS], kcnt[MAXS], scnt, us;
long long f[11][MAXS][90];

inline int check(int s) {
    static int x, lx, cnt;
    cnt = lx = 0;
    for (; s; s >>= 1) {
        x = s & 1;
        if (x) {
            if (lx)
                return -1;
            if (++cnt > m)
                return -1;
        }
        lx = x;
    }
    return cnt;
}
inline bool check2(int s, int t) {
    // Assuming s and t are legal
    static int x, y, lx, ly;
    lx = ly = 0;
    for (; s || t; s >>= 1, t >>= 1) {
        x = s & 1;
        y = t & 1;
        if (x + y + lx + ly > 1)
            return false;
        lx = x;
        ly = y;
    }
    return true;
}

int main() {
    int i, j, k, l, s, res, ub, v;
    long long ans = 0;
    scanf("%d%d", &n, &m); // slots are 0 ~ n - 1
    if (m > ((n * n) >> 1)) {
        puts("0");
        return 0;
    }

    us = (1 << n) - 1;
    for (s = 0; s <= us; ++s) {
        res = check(s);
        if (res != -1)
            st[++scnt] = s, kcnt[scnt] = res, f[1][scnt][res] = 1;
    }
    
    for (i = 2; i <= n; ++i) {
        for (j = 1; j <= scnt; ++j) {
            ub = i * (1 + n / 2);
            for (l = 0; l <= ub; ++l) {
                v = l - kcnt[j];
                if (v >= 0) {
                    for (k = 1; k <= scnt; ++k) {
                        if (check2(st[j], st[k]))
                            f[i][j][l] += f[i - 1][k][v];
                    }
                }
            }
        }
    }
    
    for (j = 1; j <= scnt; ++j)
        ans += f[n][j][m];
    printf("%lld\n", ans);
    return 0;
}
