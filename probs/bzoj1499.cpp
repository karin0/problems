#include <cstdio>
#include <algorithm>

const int MAXN = 204, MAXP = 204;

int n, m, x0, y0, p, len[MAXP], d[MAXP], f[MAXP][MAXN][MAXN];
char map[MAXN][MAXN];

struct Item {
    int t, v;
} mq[MAXN];
int head, tail;
inline void clear() {
    head = 1, tail = 0;
}
inline int size() {
    return tail - head + 1;
}
inline void push(int s, int v) {
    while (size() > 0 && v - s >= mq[tail].v)
        --tail;
    mq[++tail] = (Item){s, v - s};
}
inline int front(int s, int i) {
    while (size() > 1 && s - mq[head].t > len[i])
        ++head;
    return mq[head].v + s;
}

inline void update(int t, int x, int y, int dx, int dy) {
    clear();
    for (int s = 1; 1 <= x && x <= n && 1 <= y && y <= m; x += dx, y += dy, ++s) {
        if (map[x][y] != '.')
            clear(), f[t][x][y] = -99999999;
        else {
            push(s, f[t - 1][x][y]);
            f[t][x][y] = front(s, t);
        }
    }
}

int main() {
    int i, x, y, ans = 0;
    scanf("%d%d%d%d%d", &n, &m, &x0, &y0, &p);
    for (i = 1; i <= n; ++i)
        scanf("%s", map[i] + 1);
    for (i = 1; i <= p; ++i)
        scanf("%d%d%d", &x, &y, d + i), len[i] = y - x + 1;
    
    for (i = 0; i <= p; ++i)
        for (x = 1; x <= n; ++x)
            for (y = 1; y <= m; ++y)
                f[i][x][y] = -99999999;
    f[0][x0][y0] = 0;
    for (i = 1; i <= p; ++i) {
        if (d[i] == 1)
            for (y = 1; y <= m; ++y)
                update(i, n, y, -1, 0);
        else if (d[i] == 2)
            for (y = 1; y <= m; ++y)
                update(i, 1, y, +1, 0);
        else if (d[i] == 3)
            for (x = 1; x <= n; ++x)
                update(i, x, m, 0, -1);
        else if (d[i] == 4)
            for (x = 1; x <= n; ++x)
                update(i, x, 1, 0, +1);
    }
    
    for (x = 1; x <= n; ++x)
        for (y = 1; y <= m; ++y)
            ans = std::max(ans, f[p][x][y]);
    printf("%d\n", ans);

    return 0;
}
