#include <cstdio>
#include <algorithm>
const int MAXN = 5002;

bool killed[MAXN][MAXN];
int n, cnt;
inline bool kill(int x, int y) {
    if (x >= 1 && x <= n && y >= 1 && y <= n) {
        if (!killed[x][y])
            killed[x][y] = true, --cnt;
        return false;
    } else
        return true;
}
int main() {
    register int q, i, j, x, y, r;
    register bool r1, r2, r3, r4;
    scanf("%d%d", &n, &q);
    cnt = n * n;
    while (q--) {
        scanf("%d%d%d", &x, &y, &r);
        for (i = 0; i <= r; ++i) 
            for (j = 0; j <= r && i * i + j * j <= r * r; ++j) {
                r1 = kill(x + i, y + j);
                r2 = kill(x - i, y + j);
                r3 = kill(x - i, y - j);
                r4 = kill(x + i, y - j);
                if (r1 && r2 && r3 && r4)
                    break;
            }
    }
    printf("%d\n", cnt);
    return 0;
}
