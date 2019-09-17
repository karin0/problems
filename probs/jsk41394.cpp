#include <akari>

const int N = 18, NS = (1 << 16) + 5, X = 4002, B = 4000;
// [0, B]

/*
struct S {
    int x, y, d, l;
    S() {}
    S(int x, int y, int d, int l) : x(x), y(y), d(d), l(l) {}
};
int ans[X][X][6];
*/
int cal(int x, int y) {
    x = std::abs(x);
    y = std::abs(y);
    // return ans[x][y][0] - 1;
    if (!x && !y)
        return 0;
    if (x == 1 && y == 1)
        return 6;
    /*
    if (x > 1 && y > 1)
        return x + y;
    else if ((x && !(x & 3)) || (y && !(y & 3)))
        return x + y;
    else
        return x + y + 2;
    */
    if (x > y)
        std::swap(x, y);
    if (x <= 1)
        return x + y + (int(bool(y & 3)) << 1);
    return x + y;
}
/*
struct Q {
    S a[X * X * 6];
    int l, r; // [l, r)
    const S &pop() {
        return a[l++];
    }
    void push(const S &x) {
        int &t = ans[x.x][x.y][x.d];
        if (t)
            return;
        t = x.l;
        // ccc(x.x, x.y, x.d, x.l);
        if (x.d == 0 && t != cal(x.x, x.y) + 1)
            ccc(x.x, x.y, x.l-x.x-x.y);
        a[r++] = x;
    }
    bool empty() {
        return r <= l;
    }
} q;

int gw[] = {5, 4, 2, 3, 0, 1},
    ga[] = {2, 3, 1, 0, 4, 5},
    gs[] = {4, 5, 2, 3, 1, 0},
    gd[] = {3, 2, 0, 1, 4, 5};
*/
bool vv[X][X];
struct R {
    int x, y;
} a[N];
int f[NS][N];

int main() {
    //  0 1 2 3 4 5
    // 上 下左 右前后
    // re (i, 0, 6)
    //    assert(ga[gd[i]] == i && gw[gs[i]] == i);
    /*
    q.push(S(0, 0, 0, 1));
    while (!q.empty()) {
        const S &u = q.pop();
        int t = u.l + 1;
        if (u.y < B) q.push(S(u.x, u.y + 1, gw[u.d], t));
        if (u.y) q.push(S(u.x, u.y - 1, gs[u.d], t));
        if (u.x) q.push(S(u.x - 1, u.y, ga[u.d], t));
        if (u.x < B) q.push(S(u.x + 1, u.y, gd[u.d], t));
    }
    ccc("done");
    return 0;
*/
    int T;
    std::scanf("%d", &T);

    vv[2000][2000] = true;
    while (T--) {
        int n, cnt = 0;
        std::scanf("%d", &n);
        re (i, 0, n) {
            int x, y;
            std::scanf("%d%d", &x, &y);
            if (!vv[x + 2000][y + 2000]) {
                a[cnt].x = x;
                a[cnt++].y = y;
                vv[x + 2000][y + 2000] = true;
            }
        }
        n = cnt;
        int uni = 1 << n;
        re (s, 1, uni) {
            re (i, 0, n) if ((s >> i) & 1) {
                int t = s ^ (1 << i);
                if (t) {
                    f[s][i] = 0x3f3f3f3f;
                    re (j, 0, n) if ( ((t >> j) & 1))
                        f[s][i] = std::min(f[s][i], f[t][j] + cal(a[i].x - a[j].x, a[i].y - a[j].y));
                } else
                    f[s][i] = cal(a[i].x, a[i].y);
            }
        }
        std::printf("%d\n", *std::min_element(f[uni - 1], f[uni - 1] + n));

        re (i, 0, n)
            vv[a[i].x + 2000][a[i].y + 2000] = false;
    }
}
