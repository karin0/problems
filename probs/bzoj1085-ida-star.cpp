
// Why that?
 
#include <cstdio>
#include <algorithm>
const int N = 5;
const int MOVE = 8;
const int D_MAX = 15;
 
const int target[6][6] = {{0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1},
        {0, 0, 1, 1, 1, 1},
        {0, 0, 0, -1, 1, 1}, // -1 makes it always different
        {0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0}};
const int dx[] = {0, -1, -1, 1, 1, -2, -2, 2, 2};
const int dy[] = {0, -2, 2, -2, 2, -1, 1, -1, 1};
int space_x, space_y, map[N + 3][N + 3];
 
int d_lim;
bool dfs(int depth) {
    // printf("%d, %d\n", depth, d_lim);
    int i, j, h = 0; // h(x)
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= N; ++j) {
            if (!(i == space_x && j == space_y) && map[i][j] != target[i][j]) {
                ++h;
                if (depth + h > d_lim)
                    return false;
            }
        }
    }
    if (!h)
        return true;
    if (depth == d_lim)
        return false;
    int from_x, from_y, old_space_x = space_x, old_space_y = space_y; 
    int old_map = map[space_x][space_y]; // Why do I have to do this?
    for (i = 1; i <= MOVE; ++i) {
        from_x = space_x - dx[i];
        from_y = space_y - dy[i];
        if (from_x >= 1 && from_x <= N && from_y >= 1 && from_y <= N) {
            map[space_x][space_y] = map[from_x][from_y];
            space_x = from_x;
            space_y = from_y;
            // std::swap(map[space_x][space_y], map[from_x][from_y]);
            if (dfs(depth + 1))
                return true; // 最早发现的一定是最优解
            // std::swap(map[space_x][space_y], map[from_x][from_y]);
            space_x = old_space_x;
            space_y = old_space_y; // DO NOT USE += !!
        }
    }
    map[space_x][space_y] = old_map;  // Why do I have to do this?
    return false;
}
 
inline int ida_star() {
    d_lim = 0;
    while (!dfs(0)) { // 对于不成功的 dfs，调用前后 map 数组（当前局面）没有变化
        if (d_lim == D_MAX)
            return false;
        ++d_lim;
    }
    return true;
}
 
int main() {
    int t, i, j;
    char s[7];
    scanf("%d", &t);
    while (t--) {
        for (i = 1; i <= N; ++i) {
            scanf("%s", s);
            for (j = 1; j <= N; ++j) {
                if (s[j - 1] == '*') 
                    space_x = i, space_y = j;
                    // map[i][j] = -1;
                else
                    map[i][j] = (s[j - 1] == '1' ? 1 : 0);
            }
        }
        // printf("(%d, %d)", space_x, space_y);
        printf("%d\n", ida_star() ? d_lim : -1);
    }
 
    return 0;
}
