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
int a[52][52];
bool b[52][52];
std::pair<int, int> ops[2512];
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    rep (i, 1, n) rep (j, 1, m)
        scanf("%d", &a[i][j]);
    rep (i, 1, n) rep (j, 1, m) {
        if (a[i][j] && ((!a[i - 1][j] && !a[i + 1][j]) || 
            (!a[i][j - 1] && !a[i][j + 1])))
            return puts("-1"), 0;
    }
    int cnt = 0;
    re (i, 1, n) re (j, 1, m) {
        if (a[i][j] && a[i + 1][j] && a[i][j + 1] && a[i + 1][j + 1] && !(b[i][j] && b[i + 1][j] && b[i + 1][j + 1] && b[i][j + 1])) {
            // int x = std::min(i, n - 1);
            // int y = std::min(j, m - 1);
            // if (x > 1 && (!a[x + 1][y] || !a[x + 1][y + 1]))
            //     --x;
            // if (y > 1 && (!a[x][y + 1] || !a[x + 1][y + 1]))
            //    --y;
            int x = i, y = j;
            ops[++cnt] = std::make_pair(x, y);
            b[x][y] = b[x + 1][y] = b[x][y + 1] = b[x + 1][y + 1] = 1;
        }
    }
    // rep (i, 1, n) rep (j, 1, m)
    //    printf("%d%c", (int)b[i][j], j == m ? '\n' : ' ');
    rep (i, 1, n) rep (j, 1, m) if (a[i][j] != int(b[i][j]))
        return puts("-1"), 0;

    printf("%d\n", cnt);
    rep (i, 1, cnt)
        printf("%d %d\n", ops[i].first, ops[i].second);

}