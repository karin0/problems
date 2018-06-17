#include <cstdio>
#include <cstring>
#include <queue>

const int MAXN = 65, M = 16, INF = 0x3f3f3f3f;

int n, cnt, si, sj, ti, tj;
struct Enemy {
    int i, j;
    char c;
} enemies[M + 3];
int chess[MAXN][MAXN], guard[MAXN][MAXN];
inline bool leg(int i, int j) {
    return 1 <= i && i <= n && 1 <= j && j <= n;
}
inline void put_guard(int i, int j, int x) {
    if (leg(i, j))
        guard[i][j] |= 1 << x;
}
struct State {
    int i, j, len, rs;
};
int dis[MAXN][MAXN]; // ach[MAXN][MAXN]; // achievement = chesses removed
bool vis[MAXN][MAXN][(1 << 14) + 5];
State prev[MAXN][MAXN];
int dx[8] = {-2, -2, +2, +2, -1, -1, +1, +1}, 
    dy[8] = {-1, +1, -1, +1, -2, +2, -2, +2};
void solve() {
    static int i, j, k, ni, nj, nrs;
    memset(dis, 0x3f, sizeof(dis));
    // memset(ach, 0, sizeof(ach));
    memset(vis, false, sizeof(vis));
    State sta;
    std::queue<State> que;
    que.push((State){si, sj, 0, 0});
    dis[si][sj] = 0;
    while (!que.empty()) {
        sta = que.front();
        que.pop();
        i = sta.i;
        j = sta.j;
        // printf("(%d, %d, %d, %d)\n", i, j, sta.len, sta.rs);
        /*
        if (((ach[i][j] | sta.rs) == ach[i][j]) && dis[i][j] <= sta.len)
            continue;
        ach[i][j] |= sta.rs;
        */
        if (vis[i][j][sta.rs])
            continue;
        vis[i][j][sta.rs] = true;
        // dis[i][j] = std::min(dis[i][j], sta.len);
       
        if (i != ti || j != tj) {
            for (k = 0; k < 8; ++k) {
                ni = i + dx[k];
                nj = j + dy[k];
                if (leg(ni, nj) && ((guard[ni][nj] | sta.rs) == sta.rs)) {
                    nrs = (chess[ni][nj] == -1) ? sta.rs : (sta.rs | (1 << chess[ni][nj]));
                    if (dis[ni][nj] > sta.len + 1) {
                        dis[ni][nj] = sta.len + 1;
                        prev[ni][nj] = sta;
                    }
                    if (!vis[ni][nj][nrs])
                        que.push((State){ni, nj, sta.len + 1, nrs});
                }
            }
        }
    }
}
int main() {
    static int i, j, x, k;
    static char line[MAXN], ch;
    static bool flag[6];
    while (scanf("%d", &n) == 1) {
        memset(guard, 0, sizeof(guard));
        memset(chess, -1, sizeof(chess));
        cnt = 0;
        for (i = 1; i <= n; ++i) {
            scanf("%s", line + 1);
            for (j = 1; j <= n; ++j) {
                ch = line[j];
                if (ch == '.')
                    continue;
                if (ch == 'O') {
                    si = i;
                    sj = j;
                    continue;
                }
                enemies[cnt] = (Enemy){i, j, ch};
                chess[i][j] = cnt;
                ++cnt;
            }
        }
        for (k = 0; k < cnt; ++k) {
            i = enemies[k].i;
            j = enemies[k].j;
            switch (enemies[k].c) {
                case 'C':
                    flag[1] = true;
                    flag[2] = true;
                    flag[3] = true;
                    flag[4] = true;
                    for (x = 1; x <= n; ++x) {
                        if (flag[1] && (!leg(i - x, j) || chess[i - x][j] != -1))
                            flag[1] = false;
                        if (flag[2] && (!leg(i + x, j) || chess[i + x][j] != -1))
                            flag[2] = false;
                        if (flag[3] && (!leg(i, j - x) || chess[i][j - x] != -1))
                            flag[3] = false;
                        if (flag[4] && (!leg(i, j + x) || chess[i][j + x] != -1))
                            flag[4] = false;
                        if (flag[1])
                            guard[i - x][j] |= 1 << k;
                        if (flag[2])
                            guard[i + x][j] |= 1 << k;
                        if (flag[3])
                            guard[i][j - x] |= 1 << k;
                        if (flag[4])
                            guard[i][j + x] |= 1 << k;
                    }
                    break;
                case 'K':
                    put_guard(i - 2, j - 1, k);
                    put_guard(i - 2, j + 1, k);
                    put_guard(i + 2, j - 1, k);
                    put_guard(i + 2, j + 1, k);
                    put_guard(i - 1, j - 2, k);
                    put_guard(i - 1, j + 2, k);
                    put_guard(i + 1, j - 2, k);
                    put_guard(i + 1, j + 2, k);
                    break;
                case 'B':
                    flag[1] = true;
                    flag[2] = true;
                    flag[3] = true;
                    flag[4] = true;
                    for (x = 1; x <= n; ++x) {
                        if (flag[1] && (!leg(i - x, j - x) || chess[i - x][j - x] != -1))
                            flag[1] = false;
                        if (flag[2] && (!leg(i - x, j + x) || chess[i - x][j + x] != -1))
                            flag[2] = false;
                        if (flag[3] && (!leg(i + x, j - x) || chess[i + x][j - x] != -1))
                            flag[3] = false;
                        if (flag[4] && (!leg(i + x, j + x) || chess[i + x][j + x] != -1))
                            flag[4] = false;
                        if (flag[1])
                            guard[i - x][j - x] |= 1 << k;
                        if (flag[2])
                            guard[i - x][j + x] |= 1 << k;
                        if (flag[3])
                            guard[i + x][j - x] |= 1 << k;
                        if (flag[4])
                            guard[i + x][j + x] |= 1 << k;
                    }
                    break;
                case 'Q':
                    flag[1] = true;
                    flag[2] = true;
                    flag[3] = true;
                    flag[4] = true;
                    for (x = 1; x <= n; ++x) {
                        if (flag[1] && (!leg(i - x, j) || chess[i - x][j] != -1))
                            flag[1] = false;
                        if (flag[2] && (!leg(i + x, j) || chess[i + x][j] != -1))
                            flag[2] = false;
                        if (flag[3] && (!leg(i, j - x) || chess[i][j - x] != -1))
                            flag[3] = false;
                        if (flag[4] && (!leg(i, j + x) || chess[i][j + x] != -1))
                            flag[4] = false;
                        if (flag[1])
                            guard[i - x][j] |= 1 << k;
                        if (flag[2])
                            guard[i + x][j] |= 1 << k;
                        if (flag[3])
                            guard[i][j - x] |= 1 << k;
                        if (flag[4])
                            guard[i][j + x] |= 1 << k;
                    }
                    flag[1] = true;
                    flag[2] = true;
                    flag[3] = true;
                    flag[4] = true;
                    for (x = 1; x <= n; ++x) {
                        if (flag[1] && (!leg(i - x, j - x) || chess[i - x][j - x] != -1))
                            flag[1] = false;
                        if (flag[2] && (!leg(i - x, j + x) || chess[i - x][j + x] != -1))
                            flag[2] = false;
                        if (flag[3] && (!leg(i + x, j - x) || chess[i + x][j - x] != -1))
                            flag[3] = false;
                        if (flag[4] && (!leg(i + x, j + x) || chess[i + x][j + x] != -1))
                            flag[4] = false;
                        if (flag[1])
                            guard[i - x][j - x] |= 1 << k;
                        if (flag[2])
                            guard[i - x][j + x] |= 1 << k;
                        if (flag[3])
                            guard[i + x][j - x] |= 1 << k;
                        if (flag[4])
                            guard[i + x][j + x] |= 1 << k;
                    }
                    break;
                case 'X':
                    ti = i;
                    tj = j;
                    put_guard(i - 1, j - 1, k);
                    put_guard(i - 1, j, k);
                    put_guard(i - 1, j + 1, k);
                    put_guard(i, j - 1, k);
                    put_guard(i, j + 1, k);
                    put_guard(i + 1, j - 1, k);
                    put_guard(i + 1, j, k);
                    put_guard(i + 1, j + 1, k);
                    break;
                case 'P':
                    put_guard(i + 1, j - 1, k);
                    put_guard(i + 1, j + 1, k);
                    break;
            }
        }
        /*
            putchar('\n');
            putchar('\n');
        for (i = 1; i <= n; ++i) {
            for (j = 1; j <= n; ++j) {
                if (guard[i][j])
                    putchar('X');
                else
                    putchar('.');
            }
            putchar('\n');
        }*/
        if (guard[si][sj]) {
            puts("-1");
            continue;
        }
        for (i = 1; i <= n; ++i) {
            for (j  =1; j <= n; ++j) {
                // putchar(opt[i][j] ? opt[i][j] : '.');
                putchar(guard[i][j] ? 'X' : '.');
            }
            putchar('\n');
        }
        solve();
        printf("%d\n", dis[ti][tj] < INF ? dis[ti][tj] : -1);

        char opt[MAXN][MAXN];
        int cc = 0;
        while (ti != si || tj != sj) {
            opt[ti][tj] = '0' + cc++;
            State p = prev[ti][tj];
            printf("(%d, %d) -> (%d, %d), %d in %d\n", p.i, p.j, ti, tj, guard[ti][tj], p.rs);
            ti = p.i;
            tj = p.j;
        }
            putchar('\n');
        for (i = 1; i <= n; ++i) {
            for (j  =1; j <= n; ++j) {
                putchar(opt[i][j] ? opt[i][j] : '.');
            }
            putchar('\n');
        }
    }
    
    return 0;
}
