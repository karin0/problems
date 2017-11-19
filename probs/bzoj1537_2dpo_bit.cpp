#include <cstdio>
#include <algorithm>

const int MAXN = 1e5 + 10;

int n, p, q, yy[MAXN];

struct Point {
    int x, y, w;
} qwq[MAXN];
inline bool qaq(Point a, Point b) {
    return (a.x == b.x) ? (a.y < b.y) : (a.x < b.x);
}

int c[MAXN];
inline int lowbit(int x) {
    return x & -x;
}
inline void update(int x, int v) {
    while (x <= n)
        c[x] = std::max(c[x], v), x += lowbit(x);
}
inline int query(int x) {
    int res = -1;
    while (x > 0)
        res = std::max(res, c[x]), x -= lowbit(x);
    return res;
}

inline void read(int& res) {
    res = 0;
    char ch = 0;
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9')
        res = res * 10 + ch - '0', ch = getchar();
}
int main() {
    int i, y_pos, f, ans = 0;
    scanf("%d%d%d", &p, &q, &n);
    for (i = 1; i <= n; ++i) {
        read(qwq[i].x), read(qwq[i].y), read(qwq[i].w);
        yy[i] = qwq[i].y;
    }
    std::sort(qwq + 1, qwq + n + 1, qaq);
    std::sort(yy + 1, yy + n + 1);
    // f(i) = max{f(j) | j < i, y(j) < y(i)} + w(i)
    for (i = 1; i <= n; ++i) {
        y_pos = std::lower_bound(yy + 1, yy + n + 1, qwq[i].y) - yy;
        f = query(y_pos) + qwq[i].w;
        update(y_pos, f);
        ans = std::max(ans, f);
    }
    printf("%d\n", ans);
    
    return 0;
}
