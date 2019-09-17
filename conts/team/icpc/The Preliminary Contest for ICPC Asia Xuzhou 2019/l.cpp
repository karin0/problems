#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cassert>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)
typedef long long ll;
typedef const int cint;

#ifdef AKARI
void cca() {
    std::cerr << "\033[39;0m" << std::endl;
}
template <typename T, typename... Args>
void cca(T a, Args... args) {
    std::cerr << a << ", ";
    cca(args...);
}
    #define ccc(args...) std::cerr << "\033[32;1m" << #args << "  =  ", cca(args)
    #define ccf(args...) fprintf(stderr, args)
    #define crep(i_, s_, t_) rep(i, s_, t_)
#else
    #define ccc(...) 0
    #define ccf(...) 0
    #define crep(...) if (0)
#endif

const int N = 18, NS = (1 << 16) + 5, X = 4002, B = 4000;
// [0, B]

struct S {
    int x, y, d, l;
    S() {}
    S(int x, int y, int d, int l) : x(x), y(y), d(d), l(l) {
    }
};
int ans[X][X][6];
int cal(int x, int y) {
    x = std::abs(x);
    y = std::abs(y);
    // return ans[x][y][0] - 1;
    if (!x && !y)
        return 0;
    if (x == 1 && y == 1)
        return x + y + 4;
    if (x > 1 && y > 1)
        return x + y;
    else if ((x && !(x & 3)) || (y && !(y & 3)))
        return x + y;
    else
        return x + y + 2;
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
    scanf("%d", &T);

    vv[0][0] = true;
    while (T--) {
        int n, cnt = 0;
        scanf("%d", &n);
        re (i, 0, n) {
            int x, y;
            scanf("%d%d", &x, &y);
            if (!vv[x][y]) {
                a[cnt].x = x;
                a[cnt++].y = y;
                vv[x][y] = true;
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
        printf("%d\n", *std::min_element(f[uni - 1], f[uni - 1] + n));

        re (i, 0, n)
            vv[a[i].x][a[i].y] = false;
    }
}
