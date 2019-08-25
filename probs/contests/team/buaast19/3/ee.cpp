#include <cstdio>
#include <algorithm>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)

const int N = 100003;
int fa[N];
int find(int x) {
    return x == fa[x] ? x : (fa[x] = find(fa[x]));
}

struct S {
    int u, v, l, r;
} a[N];
int main() {
    int n, m, mr = 0;
    scanf("%d%d", &n, &m);
    rep (i, 1, m) {
        S &x = a[i];
        scanf("%d%d%d%d", &x.u, &x.v, &x.l, &x.r);
        mr = std::max(mr, x.r);
    }

    int ans = 0;
    rep (t, 1, mr) {
        rep (i, 1, n)
            fa[i] = i;
        rep (i, 1, m) {
            S &x = a[i];
            if (x.l <= t && t <= x.r && find(x.u) != find(x.v))
                fa[find(x.u)] = find(x.v);
        }
        if (find(1) == find(n))
            ++ans;
    }
    printf("%d\n", ans);

    return 0;
}