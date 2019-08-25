#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)
typedef long long ll;

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
    #define crep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#else
    #define ccc(...) 0
    #define ccf(...) 0
    #define crep(...) if (0)
#endif

#ifndef AKARI
    #define FI "fragmentation"
#endif

const int N = 100003, z = 100002;
int a[N], ha[N], w[N], val[N], _f[N], _g[N], pos[N];
bool ok[N];
std::vector<int> vec[N], pre[N];
std::vector<bool> ijn[N];
int main() {
#ifdef FI
    freopen(FI ".in", "r", stdin);
    freopen(FI ".out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);
    rep (i, 1, n) {
        scanf("%d", &a[i]);
        ha[i] = a[i];
    }
    std::sort(ha + 1, ha + n + 1);
    int *end = std::unique(ha + 1, ha + n + 1);
    int mx = end - ha - 1; // 1 -> mx
    int p = 0, uc = 0;
    a[0] = val[0] = -114514;
    rep (i, 1, n) {
        a[i] = std::lower_bound(ha + 1, end, a[i]) - ha;
        if (a[i] != a[i - 1]) {
            vec[a[i]].push_back(p = ++uc);
            val[p] = a[i];
            // w[p] = 1;
            pos[p] = i;
            ccc(p, val[p]);
        } else
            ++w[a[i]];
    }

    int *f = _f, *g = _g;
    rep (i, 1, mx) {
        ccc(i, w[i]);
        int siz = vec[i].size();
        f[z] = f[z - 1] = -1;
        for (int j = 0; j < siz; ++j) {
            int v = vec[i][j];
            if (val[v - 1] == i - 1) {
                if (vec[i - 1].size() == 1) {
                    f[j] = g[g[z]] + w[i] + 1;
                    pre[i].push_back(0);
                } else {
                    int q = std::lower_bound(vec[i - 1].begin(), vec[i - 1].end(), v - 1) - vec[i - 1].begin();
                    if (g[z] == q)
                        f[j] = g[g[z - 1]] + w[i] + 1, pre[i].push_back(g[z - 1]);
                    else
                        f[j] = g[g[z]] + w[i] + 1, pre[i].push_back(g[z]);
                }
                ijn[i].push_back(true);
            } else
                f[j] = g[g[z]] + w[i], pre[i].push_back(g[z]), ijn[i].push_back(false);
            ccc(i, j, vec[i][j], f[j]);
            if (f[z] < 0 || f[j] > f[f[z]])
                f[z - 1] = f[z], f[z] = j;
            else if (f[z - 1] < 0 || f[j] > f[f[z - 1]])
                f[z - 1] = j;
        }
        ccc(f[z], f[z - 1]);
        std::swap(f, g);
    }
    ccc(g[g[z]]);
    printf("%d\n", n - g[g[z]]);

    int u = g[z];
    for (int i = mx; i >= 2; --i) {
        /*
        int siz = vec[i].size();
        for (int j = 0; j < siz; ++j) {
            int v = vec[i][j];
            if (val[v - 1] == i - 1) {

            }
        */
        if (ijn[i][u])
            ok[pos[vec[i][u]]] = true;
        u = pre[i][u];
    }

    int qqq = 0;
    ok[1] = 1;
    rep (i, 1, n) {
        if (ok[i] || a[i] == a[i - 1])
            ++qqq;
        else
            printf("%d ", qqq), qqq = 1;
    }
    printf("%d\n", qqq);
}