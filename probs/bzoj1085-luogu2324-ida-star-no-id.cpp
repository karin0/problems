// Why that?
// 最早发现的不一定最优。

#include <cstdio>
#include <algorithm>
const int N = 5;
const int MOVE = 8;
const int D_MAX = 15;

void assert(bool x) {
    if (!x) {
        while (true) {
        
        printf("Damn it!");
        };
    }
    
}

const int target[6][6] = {{0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1},
        {0, 0, 1, 1, 1, 1},
        {0, 0, 0, -1, 1, 1}, // -1 makes it always different
        {0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0}};
const int dx[] = {0, -1, -1, 1, 1, -2, -2, 2, 2};
const int dy[] = {0, -2, 2, -2, 2, -1, 1, -1, 1};
int space_x, space_y, map[N + 3][N + 3];
int d_lim, d_suc;
bool dfs(int depth) {
    //printf("%d, %d, %d\n", depth, d_lim, d_suc);
    int i, j, h = 0;
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= N; ++j) {
            if (map[i][j] != target[i][j]) {
                ++h;
                if (depth + h > d_suc)
                    return false;
            }
        }
    }
    if (!h) {
        if (d_suc > depth)
            d_suc = depth;
        assert(space_x == 3 && space_y == 3);
        //printf("Yeah\n");
        return true;
    }
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
            dfs(depth + 1);
            //    return true;
            space_x = old_space_x;
            space_y = old_space_y; // DO NOT USE += !!
            map[space_x][space_y] = old_map;
            // map[from_x][from_y] = old_map;
            // std::swap(map[space_x][space_y], map[from_x][from_y]);
        }
    }
    return false;
}

inline bool a_star() {
    d_suc = D_MAX + 1;
    dfs(0);
    return d_suc <= D_MAX;
}

int main() {
    int t, i, j;
    char s[7];
    scanf("%d", &t);
    while (t--) {
        for (i = 1; i <= N; ++i) {
            scanf("%s", s);
            for (j = 1; j <= N; ++j) {
                if (s[j - 1] == '*') {
                    space_x = i, space_y = j;
                    // map[i][j] = -1;
                }
                else
                    map[i][j] = (s[j - 1] == '1' ? 1 : 0);
            }
        }
        printf("%d\n", a_star() ? d_suc : -1);
    }

    return 0;
}
