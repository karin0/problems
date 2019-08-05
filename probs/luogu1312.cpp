#include <cstdio>
#include <cstring>
#include <algorithm>
using std::swap;
const int n = 5, m = 7;
int p, g[n + 3][m + 3];
bool rm[n + 3][m + 3];
struct Move {
    int x, y, d;
} mv[6];
void fall(int i) {
    for (int j = 0, cur = 0, *col = g[i]; j < m; ++j)
        if (col[j]) {
            int t = col[j];
            col[j] = 0;
            col[cur++] = t;
        }
}
bool proc_column(int i) {
    int j, *col = g[i], k;
    int cnt = (col[0] != 0);
    bool *rmi = rm[i], res = true;
    for (j = 1; j <= m; ++j) {
        if (col[j] == col[j - 1] && col[j] != 0)
            ++cnt;
        else {
            if (cnt >= 3) {
                res = false;
                for (k = j - cnt; k < j; ++k)
                    rmi[k] = true; // printf("[Removing %d, %d]\n", i, k);
            }
            cnt = col[j] != 0;
        }
    }
    return res;
}
bool proc_line(int j) {
    int i, cnt = (g[0][j] != 0), k;
    bool res = true;
    for (i = 1; i <= n; ++i) {
        if (g[i][j] == g[i - 1][j] && g[i][j] != 0)
            ++cnt;
        else {
            if (cnt >= 3) {
                res = false;
                for (k = i - cnt; k < i; ++k)
                    rm[k][j] = true; // printf("[Removing %d, %d]\n", k, j);
            }
            cnt = (g[i][j] != 0);
        }
    }
    return res;
}
/*void show() {
    putchar('\n');
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            printf("%d ", g[i][j]);
        putchar('\n');
    }
}*/
bool dfs(int step) { // 之前已经进行了 step 步
    int i, j;
    if (step > 0) {
        bool flag = false;
        while (true) {
            for (i = 0; i < n; ++i)
                fall(i);
            flag = true;
            for (i = 0; i < n; ++i)
                flag = proc_column(i) && flag; // 最痛苦的就是这个短路求值
            for (j = 0; j < m; ++j)
                flag = proc_line(j) && flag;
            if (flag)
                break;
            else
                for (i = 0; i < n; ++i)
                    for (j = 0; j < m; ++j)
                        if (rm[i][j])
                            g[i][j] = 0, rm[i][j] = false;
        }
    }
    /*
    bool ck = true;
    for (i = 0; i < n; ++i)
        for (j = 0; j < m; ++j)
            if (g[i][j] != cv[i][j])
                ck = false;
    if (mv[0].x == 2 && mv[0].y == 0 && mv[0].d == 1 
    &&  mv[1].x == 1 && mv[1].y == 1 && mv[1].d == 1
            && step == 2)
        mt = true;
    if (mt)
       show(), scanf("%c", &ch);*/
    if (step == p) {
        for (i = 0; i < n; ++i)
            if (g[i][0])
                return false;
        return true;
    }
    int old[n + 3][m + 3];
    memcpy(old, g, sizeof(g));
    for (i = 0; i < n; ++i) {
        for (j = 0; j < m && g[i][j]; ++j) {
            // 优先右移 (1)，不需进行左交换
            if (i + 1 < n) { // 右移（右交换）
                swap(g[i][j], g[i + 1][j]);
                if (dfs(step + 1)) {
                    mv[step] = (Move){i, j, 1};
                    return true;
                }
                memcpy(g, old, sizeof(old));
            }
            if (i - 1 >= 0 && g[i - 1][j] == 0) { // 左移
                swap(g[i][j], g[i - 1][j]);
                if (dfs(step + 1)) {
                    mv[step] = (Move){i, j, -1};
                    return true;
                }
                memcpy(g, old, sizeof(old));
            }
        }
    }
    return false;
}

int main() {
    static int i, j;
    scanf("%d", &p);
    for (i = 0; i < n; ++i) {
        for (j = 0; ; ++j) {
            scanf("%d", g[i] + j);
            if (g[i][j] == 0)
                break;
        }
    }
    if (dfs(0)) {
        for (i = 0; i < p; ++i)
            printf("%d %d %d\n", mv[i].x, mv[i].y, mv[i].d);
    } else
        puts("-1");
    return 0;
}
