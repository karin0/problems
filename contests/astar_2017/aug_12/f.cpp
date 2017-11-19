#include <cstdio>
#include <cstring>

const int MAXN = 104;

int n, m, cnt_1, x_1, y_1, x_0, y_0;
char map[MAXN][MAXN];

int dx[4] = {-1, 1, 0, 0},
    dy[4] = {0, 0, -1, 1};
bool vis[MAXN][MAXN];
char tar;
int res_dfs;
inline void _dfs(int i, int j) {
    vis[i][j] = true;
    ++res_dfs;
    int ni, nj;
    for (int d = 0; d < 4; ++d) {
        ni = i + dx[d];
        nj = j + dy[d];
        if (ni <= n && ni >= 1 && nj <= m && nj >= 1 && (!vis[ni][nj]) && map[ni][nj] == tar)
            _dfs(ni, nj);
    }
}
inline int dfs(int i, int j) {
    //for (int x = 1; x <= n; ++x)
    //    for (int y = 1; y <= n; ++y)
    //        vis[x][y] = false;
    tar = map[i][j];
    res_dfs = 0;
    _dfs(i, j);
    return res_dfs;
}

inline int find() { // 寻找被 1 包围的块中的一个 0
    int i, j, nj;
    for (i = 1; i <= n; ++i) {
        for (j = 2; j <= m; ++j) {
            if (!vis[i][j] && map[i][j - 1] == '1' && map[i][j] == '0') {
                for (nj = j + 1; nj <= m; ++nj) {
                    if (map[i][nj] == '1')
                        return i * 1000 + j;
                }
            }
        }
    }
    return -1;
}

int main() {
    int i, j, x, y;
    while (scanf("%d%d", &n, &m) == 2) {
        for (int x = 1; x <= n; ++x)
            for (int y = 1; y <= n; ++y)
                vis[x][y] = false;
        x_1 = 0, y_1 = 0, x_0 = 0, y_0 = 0;
        cnt_1 = 0;
        for (i = 1; i <= n; ++i) {
            scanf("%s", &map[i][1]);
            for (j = 1; j <= m; ++j) {
                if (map[i][j] == '1') {
                    ++cnt_1;
                    if (!x_1)
                        x_1 = i, y_1 = j;
                }
            }
        }
        if (dfs(x_1, y_1) != cnt_1) {
            printf("-1\n");
            continue;
        }
        /*for (int x = 1; x <= n; ++x)
            for (int y = 1; y <= n; ++y)
                vis[x][y] = false;*/
        x = find();
        if (x == -1) {
            printf("1\n");
            continue;
        }
        y = x % 1000;
        x /= 1000;
        if (dfs(x, y) == m * n - cnt_1) {
            printf("0\n");
            continue;
        }
        printf(find() == -1 ? "0\n" : "-1\n");
    }

    return 0;
}
