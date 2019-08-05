#include <cstdio>
typedef long long LL;
const int MAXN = 505;
const LL MOD = 1000000007;
const LL BASE = 31;

int n, m;
LL ans;
char map[MAXN][MAXN];
LL qpow(LL x, int p) {
    LL res = 1;
    for (; p; p >>= 1, x = (x * x) % MOD)
        if (p & 1)
            res = (res * x) % MOD;
    return res;
}
int dx[] = {0, 1}, dy[] = {1, 0};
void dfs_2(int x, int y, int step, LL ha) { // |s| % 2 == 0
    int nx, ny;
    if (x == n && y == m) {
        ++ans;
        if (ans >= MOD)
            ans -= MOD;
        return;
    }
    for (int d = 0; d < 2; ++d) {
        nx = x + dx[d];
        ny = y + dy[d];
        if (nx < 1 || nx > n || ny < 1 || ny > m)
            continue;
        if (step <= (n + m - 1) / 2) {
            dfs_2(nx, ny, step + 1, (ha * BASE + map[nx][ny] - 'a') % MOD);
        } else {
            if (map[nx][ny] - 'a' == ha / BASE)
                dfs_2(nx, ny, step + 1, ha / BASE);
        }
    }
}
void dfs_1(int x, int y, int step, LL ha) {
    int nx, ny;
    if (x == n && y == m) {
        ++ans;
        if (ans >= MOD)
            ans -= MOD;
        return;
    }
    for (int d = 0; d < 2; ++d) {
        nx = x + dx[d];
        ny = y + dy[d];
        if (nx < 1 || nx > n || ny < 1 || ny > m)
            continue;
        if (step < (n + m) / 2)
            dfs_1(nx, ny, step + 1, (ha * BASE + map[nx][ny] - 'a') % MOD);
        else if (step == (n + m) / 2) 
            dfs_1(nx, ny, step + 1, ha);
        else {
            if (map[nx][ny] - 'a' == ha / BASE)
                dfs_1(nx, ny, step + 1, ha / BASE);
        }
    }
}


int main() {
    int i, j;
    bool spe = true;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i) {
        scanf("%s", &map[i][1]);
    }
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= n; ++j) { 
            if (map[i][j] != 'a') {
                spe = false;
                break;
            }
        }
        if (!spe)
            break;
    }
    if (spe) {
        ans = qpow(2LL, n + m - 2);
        printf("%lld\n", ans);
        return 0;
    }
    if ((n + m) % 2)
        dfs_2(1, 1, 1, map[1][1] - 'a');
    else
        dfs_1(1, 1, 1, map[1][1] - 'a');
    printf("%lld\n", ans);
    return 0;
}
