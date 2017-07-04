#include <cstdio>
#include <cstring>
#include <queue>
#define MAXN 1010
#define LEGAL(i, j) ((1 <= (i) <= h) && (1 <= (j) <= w) && map[(i)][(j)] == '.')
#define BFSTO(i, j) if(!vis[(i)][(j)] && LEGAL((i), (j))) {que.push(Point((i), (j))); f[(i)][(j)][1] = f[x][y][1] + 1; vis[(i)][(j)] = true;}


int h, w, d, r;
char map[MAXN][MAXN];
int f[MAXN][MAXN][1];
// 走到(i, j)，还能否使用能力(1 / 0)时走的最小步数

struct Point {
    int x, y;
    Point(int i, int j): x(i), y(j) {};
};

bool vis[MAXN];
void bfs(int x, int y) {
    std::queue<Point> que;
    que.push(Point(x, y));
    f[x][y][1] = 0;
    while (!que.empty()) {
        Point p = que.front();
        int &x = p.x, &y = p.y;
        que.pop();
        BFSTO(x - 1, y);
        BFSTO(x + 1, y);
        BFSTO(x, y - 1);
        BFSTO(x, y + 1);
    }
}


int main() {
    scanf("%d%d%d%d", &h, &w, &d, &r);
    int i, j;
    for (i = 1; i <= h; ++i) {
        for (j = 1; j <= w; ++j) {
            scanf("%d", &map[i][j]);
        }
    }
    memset(f, 0x3f, sizeof(f));
    bfs(1, 1);
    for (i = 1; i <= h; ++i) {
        for (j = 1; j <= w; ++j) {
            if (LEGAL(i - 1, j) f[i][j][1] = min(f[i][j][1], f[i - 1][j][1]);
            
            if (LEGAL(i - 1, j) f[i][j][1] = min(f[i][j][1], f[i - 1][j][1]);
            if (LEGAL(i - 1, j) f[i][j][1] = min(f[i][j][1], f[i - 1][j][1]);
        }
    }
    
    printf("%d\n", min())

    return 0;
}
