#include <cstdio>
#include <algorithm>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)

const int N = 3003;
char a[N][N];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    rep (i, 1, n) {
        scanf("%s", a[i] + 1);
        rep (j, 1, m) {
            a[i][j] -= '0';
            // s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + a[i][j];
        }
    }
    int ans = 0;
    rep (x1, 1, n) {
        rep (y1, 1, m) {
            rep (x2, x1, n) {
                rep (y2, y1, m) {
                    bool ok = true;
                    rep (i, x1, x2) {
                        rep (j, y1, y2) {
                            if (!a[i][j]) {
                                ok = false;
                                break;
                            }
                        }
                        if (!ok)
                            break;
                    }
                    if (!ok)
                        continue;
                    ok = false;
                    rep (i, x1, x2)
                        if (a[i][y1 - 1] != 1) {
                            ok = true;
                            break;
                        }
                    if (!ok)
                        continue;
                    ok = false;
                    rep (i, x1, x2)
                        if (a[i][y2 + 1] != 1) {
                            ok = true;
                            break;
                        }
                        
                    if (!ok)
                        continue;
                    ok = false;
                    rep (i, y1, y2)
                        if (a[x1 - 1][i] != 1) {
                            ok = true;
                            break;
                        }

                    if (!ok)
                        continue;
                    ok = false;
                    rep (i, y1, y2) 
                        if (a[x2 + 1][i] != 1) {
                            ok = true;
                            break;
                        }
                    if (ok) {
                        ++ans;
                        // printf("(%d, %d), (%d, %d)\n", x1, y1, x2, y2);
                    }
                }
            }
        }
    }
    printf("%d\n", ans);

    return 0;
}