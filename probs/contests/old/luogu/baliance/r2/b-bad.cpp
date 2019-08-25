#include <cstdio>
#include <algorithm>

const int MAXN = 100005;
int n, m, b = 30;
struct Cond {
    int y, n, l;
} cond[32][MAXN]; // Bit 0 ~ 29
bool a[MAXN];
int cnt1[MAXN], ans[MAXN];

int main() {
    static int i, l, r, p, x, vn;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; ++i) {
        scanf("%d%d%d", &l, &r, &p);
        for (x = 0; x < b; ++x, p >>= 1) {
            // 第 x 位的限制
            if (p & 1) {
                cond[x][l].y = 1;
                cond[x][r + 1].y = -1;
                cond[x][r + 1].l = l;
            } else {
                cond[x][l].n = 1;
                cond[x][r + 1].n = -1;
                cond[x][r + 1].l = l;
            }
        }
    }
    // vy = 0, vn = 0, cnt1 = 0;
    for (x = 0; x < b; ++x) {
        Cond *cx = cond[x];
        cnt1[0] = 0;
        for (i = 1; i <= n; ++i) {
            if (cx[i].y == -1) {
                if (cnt1[i - 1] - cnt1[cx[i].l - 1] == 0) {
                    puts("No");
                    return 0;
                }
            }
            vn += cx[i].n;
            if (vn)
                cnt1[i] = cnt1[i - 1];
            else
                a[i] = true, cnt1[i] = cnt1[i - 1] + 1;
            ans[i] += a[i] << x;
        }
        if (cx[n + 1].y == -1) {
            if (cnt1[b] - cnt1[cx[n + 1].l - 1] == 0) {
                puts("No");
                return 0;
            }
        }
    }
    puts("Yes");
    for (i = 1; i <= n; ++i) {
        printf("%d", ans[i]);
        if (i < n)
            putchar(' ');
    }
    putchar('\n');

    return 0;
}
