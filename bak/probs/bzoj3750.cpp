#include <cstdio>
#include <algorithm>

const int N = 1003;
int n, m, a, b, scnt, tcnt, left;
bool tar[N][N];
struct Point {
    int x, y;
} sp[N * N], tp[N * N];
int main() {
    static int orz, i, j, dx, dy, nx, ny;
    static char line[N];
    static bool x, fail;
    scanf("%d", &orz);
    while (orz--) {
        scanf("%d%d%d%d", &n, &m, &a, &b);
        for (i = 1; i <= n; ++i) {
            scanf("%s", line + 1);
            for (j = 1; j <= m; ++j) {
                tar[i][j] = x = (line[j] == 'x');
                if (x)
                    tp[++tcnt] = (Point){i, j};
            }
        }
        for (i = 1; i <= a; ++i) {
            scanf("%s", line + 1);
            for (j = 1; j <= b; ++j)
                if (line[j] == 'x')
                    sp[++scnt] = (Point){i, j};
        }
        left = tcnt;
        fail = false;
        for (i = 1; !fail && left && i <= tcnt; ++i) {
            if (!tar[tp[i].x][tp[i].y])
                continue;
            tar[tp[i].x][tp[i].y] = false, --left;
            dx = tp[i].x - sp[1].x;
            dy = tp[i].y - sp[1].y;
            fail = false;
            for (j = 2; j <= scnt; ++j) {
                nx = sp[j].x + dx;
                ny = sp[j].y + dy;
                if (nx <= n && ny <= m && tar[nx][ny])
                    tar[nx][ny] = false, --left;
                else {
                    fail = true;
                    break;
                }
            }
        }
        puts((fail || left) ? "NIE" : "TAK");
        tcnt = scnt = 0; // clear
    }
    return 0;
}
