#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
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

#define chk(a, b, c, d) if (z[a] == z[b] && z[a] == z[c] && z[a] == z[d]) ++res;
#define L(a, b, c, d) z[a] = t[b], z[b] = t[c], z[c] = t[d], z[d] = t[a];
#define LL(a, b, c, d, e, f, g, h) z[a] = t[c], z[b] = t[d], z[c] = t[e], z[d] = t[f], z[e] = t[g], z[f] = t[h], z[g] = t[a], z[h] = t[b];
#define R(a, b, c, d) z[b] = t[a], z[c] = t[b], z[d] = t[c], z[a] = t[d];
#define RR(a, b, c, d, e, f, g, h) z[c] = t[a], z[d] = t[b], z[e] = t[c], z[f] = t[d], z[g] = t[e], z[h] = t[f], z[a] = t[g], z[b] = t[h];
#define F(a, b, c, d, A, B, C, D, E, F, G, H, o) \
    if (la != o + 1) { \
        L(a, b, c, d); \
        LL(A, B, C, D, E, F, G, H); \
        dfs(p + 1, o); \
    } \
    if (la != o) { \
        R(a, b, c, d); \
        RR(A, B, C, D, E, F, G, H); \
        dfs(p + 1, o + 1); \
    } \
    z[a] = t[a], z[b] = t[b], z[c] = t[c], z[d] = t[d]; \
    z[A] = t[A], z[B] = t[B], z[C] = t[C], z[D] = t[D], z[E] = t[E], z[F] = t[F], z[G] = t[G], z[H] = t[H];

int n, z[24], ans = 0;
void dfs(int p, int la) {
    int res = 0;
    chk(0, 1, 2, 3);
    chk(4, 5, 10, 11);
    chk(6, 7, 12, 13);
    chk(8, 9, 14, 15);
    chk(16, 17, 18, 19);
    chk(20, 21, 22, 23);
    ans = std::max(ans, res);
    if (p >= n)
        return;
    int t[24];
    memcpy(t, z, sizeof(*z) * 24);
    F(6, 7, 13, 12, 2, 3, 8, 14, 17, 16, 11, 5, 0)
    F(4, 5, 11, 10, 0, 2, 6, 12, 16, 18, 20, 22, 2)
    F(0, 1, 3, 2, 22, 23, 9, 8, 7, 6, 5, 4, 4)
}

int main() {
    while (scanf("%d", &n) == 1) {
        ans = 0;
        re (i, 0, 24)
            scanf("%d", &z[i]);
        dfs(0, -1);
        printf("%d\n", ans);
    }
}