#include <cstdio>
#include <algorithm>
#include <iostream>
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
    #define FI "instruction"
#endif

int pre[200], dep[200], lc[200], rc[200], num[200];
bool stat[200];
struct S {
    int t, u;
    bool on;
    bool operator < (const S &rhs) const {
        return t < rhs.t;
    }
} a[53005];
int cnt;

int main() {
#ifdef FI
    freopen(FI ".in", "r", stdin);
    freopen(FI ".out", "w", stdout);
#endif
    int n;
    scanf("%d", &n);
    
    char typ[2], id[2];
    rep (i, 1, n) {
        int fa;
        scanf("%s%d", typ, &fa);
        pre[i] = fa;
        if (lc[fa])
            rc[fa] = i;
        else
            lc[fa] = i;
        dep[i] = dep[fa] + 1;
        if (typ[0] == 'p') {
            scanf("%s", id);
            num[id[0]] = i;
        }
    }
    int m;
    scanf("%d", &m);
    while (m--) {
        int t;
        scanf("%d%s", &t, id);
        int u = num[id[0]];
        while (u) {
            int fa = pre[u];
            if (!fa)
                break;
            S &tag = a[++cnt];
            tag.t = t + dep[fa];
            tag.u = fa;
            tag.on = (u == rc[fa]);

            u = fa;
        }
    }
    std::sort(a + 1, a + cnt + 1);
    int cc = 0;
    rep (i, 1, cnt) {
        S &tag = a[i];
        if (tag.on != stat[tag.u]) {
            stat[tag.u] ^= 1;
            ++cc;
        }
    }
    rep (i, 0, n)
        stat[i] = false;
    printf("%d\n", cc);
    rep (i, 1, cnt) {
        S &tag = a[i];
        if (tag.on != stat[tag.u]) {
            printf("%d %d\n", tag.u, tag.t);
            stat[tag.u] ^= 1;
        }
    }
}