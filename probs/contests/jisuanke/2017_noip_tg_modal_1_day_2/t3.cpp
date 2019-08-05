#include <cstdio>
#include <queue>
#include <map>
#include <algorithm>
#define SPA 233
#define OBS -1
const int MAXN = 13;
const int MAXP = 13;
const int MAXS = 1 << 12;

int n, m, k0, p, dk[MAXP];
int map[MAXN][MAXN], si, sj, ti, tj;
char line[MAXN];
long long ans = 2147483600, lans = 2147483600, scnt = 0;

struct State {
    int x, y, s;
    long long k, w;
    State(int x, int y, int s, long long k, long long w): x(x), y(y), s(s), k(k), w(w) {}
};
int dx[] = {0, -1, 0, 1};
int dy[] = {1, 0, -1, 0};
// f(i, j, k, S) 表示走到(i, j),完成了救不救这个人(若有)后单位位移代价为 k ,已经救了 S 中村民的最小代价
std::queue<State> que;
std::map<long long, long long> cost[MAXN][MAXN][MAXS];
inline void try_push(State sta) {
    if (!cost[sta.x][sta.y][sta.s].count(sta.k)) {
        cost[sta.x][sta.y][sta.s][sta.k] = sta.w;
        que.push(sta);
    } else if (cost[sta.x][sta.y][sta.s][sta.k] > sta.w) {
            cost[sta.x][sta.y][sta.s][sta.k] = sta.w;
            que.push(sta);
        }
}
inline void bfs() {
    // (s >> i) & 1 : 第 i 个村民是否属于 s
    que.push(State(si, sj, 0, k0, 0));
    State now = State(0, 0, 0, 0, 0);
    int mm, nx, ny;
    while (!que.empty()) {
        if (ans == lans) {
            ++scnt;
            if (scnt > n * m * 300)
                break;
        }
        lans = ans;
        now = que.front();
        que.pop();
        int tk = std::max(now.k, 1LL);
        printf("It is (%d, %d, %d, %lld, %lld), %lld\n", now.x, now.y, now.s, now.k, now.w, ans);
        if (now.x == ti && now.y == tj && now.s == 0) {
            ans = std::min(ans, now.w);
            continue;
        }
        for (int d = 0; d < 4; ++d) {
            nx = now.x + dx[d];
            ny = now.y + dy[d];
            mm = map[nx][ny];
            if (mm == SPA)
                if (nx == ti && ny == tj) {
                    for (int t = 0; t <= now.s; ++t)
                        if ((now.s | t) == now.s) {
                            int nk = now.k;
                            for (int i = 1; i <= p; ++i)
                                if (!((t >> i) & 1))
                                    nk -= dk[i];
                            try_push(State(nx, ny, t, nk, now.w + tk));
                        }
                } else
                    try_push(State(nx, ny, now.s, now.k, now.w + tk));
            else if (mm == -1 || mm == 0)
                continue;
            else {
                try_push(State(nx, ny, now.s, now.k, now.w + tk));
                if (!((now.s >> mm) & 1)) {
                    try_push(State(nx, ny, now.s | (1 << m), now.k + dk[mm], now.w + tk));
                }
            }
        }
    }

}

int main() {
    register int i, j;
    register char c;
    scanf("%d%d%d", &n, &m, &k0);
    for (i = 1; i <= n; ++i) {
        scanf("%s", line);
        for (j = 1; j <= m; ++j) {
            c = line[j - 1];
            if (c == '.')
                map[i][j] = SPA;
            else if (c == '#')
                map[i][j] = -1;
            else if (c == 's')
                map[i][j] = SPA, si = i, sj = j;
            else if (c == 't')
                map[i][j] = SPA, ti = i, tj = j;
            else
                map[i][j] = c - 'A' + 1, ++p;
        }
    }
    //uni = (1 << (p + 1)) - 1;
    for (i = 1; i <= p; ++i) {
        scanf("%s%d", line, &j);
        dk[line[0] - 'A' + 1] = j;
    }
    bfs();
    printf("%lld\n", ans);
    return 0;
}
