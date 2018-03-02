#include <cstdio>
#include <algorithm>

const int MAXN = 2003, INF = 2147483600;
int n, m, a[MAXN][MAXN], xl, yl;
int reach[MAXN], mode;
inline void set_mode(int x) {
    mode = x;
    if (mode == 1 || mode == 2 || mode == 5 || mode == 6)
        xl = n, yl = m;
    else
        xl = m, yl = n;
}
inline int getv(int x, int y) {
    if (mode == 1)
        return a[n + 1 - x][m + 1 - y];
    if (mode == 2)
        return a[x][m + 1 - y];
    if (mode == 3)
        return a[y][x];
    if (mode == 4)
        return a[y][m + 1 - x];
    if (mode == 5)
        return a[x][y];
    if (mode == 6)
        return a[n + 1 - x][y];
    if (mode == 7)
        return a[n + 1 - y][m + 1 - x];
    else
        return a[n + 1 - y][x];
}
bool _check(int x) {
    static int mx, mn, mj, i, j, nx, nn;
    mx = getv(1, 1);
    mn = mx;
    mj = yl;
    for (i = 1; i <= xl; ++i) {
        for (j = 1; j <= mj; ++j) {
            nx = std::max(mx, getv(i, j));
            nn = std::min(mn, getv(i, j));
            if (nx - nn > x)
                break;
            mx = nx;
            mn = nn;
        }
        if (nx - nn > x)
            mj = j - 1;
        else
            mj = j;
        reach[i] = mj;
    }
    if (mx - mn > x)
        return false;
    if (reach[xl] == yl)
        return true;
    mx = mn = getv(xl, reach[xl] + 1);
    for (i = 1; i <= xl; ++i) {
        for (j = reach[i] + 1; j <= yl; ++j) {
            mx = std::max(mx, getv(i, j));
            mn = std::min(mn, getv(i, j));
            if (mx - mn > x)
                return false;
        }
    }
    return true;
}
bool check(int x) {
    static int i;
    for (i = 1; i <= 3; ++i) {
        set_mode(i);
        if (_check(x)) {
            return true;
        }
    }
    return false;
}

int main() {
    int i, j, mn, mx, l, r, x;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= m; ++j) {
            scanf("%d", a[i] + j);
            if (i == 1 && j == 1)
                mn = mx = a[1][1];
            else
                mn = std::min(mn, a[i][j]), mx = std::max(mx, a[i][j]);
        }
    l = 0, r = mx - mn; // (l, r]
    while (r - l > 1) {
        x = (l + r) >> 1;
        if (check(x))
            r = x;
        else
            l = x;
    }
    
    printf("%d\n", r);
    return 0;
}
