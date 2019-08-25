#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

const int MAXN = 100005;
int n, m, b = 30;
int c[32][MAXN]; // Bit 0 ~ 29
struct Cond {
    int l, r;
};
std::vector<Cond> conds[32];
bool a[MAXN];
int cnt1[MAXN], ans[MAXN];

int main() {
    static int i, l, r, p, v, x;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; ++i) {
        scanf("%d%d%d", &l, &r, &p);
        for (x = 0; x < b; ++x, p >>= 1) {
            // 第 x 位的限制
            if (p & 1) {
                conds[x].push_back((Cond){l, r});
            } else {
                c[x][l] += 1;
                c[x][r + 1] += -1;
            }
        }
    }
    cnt1[0] = 0;
    for (x = 0; x < b; ++x) {
        int *cx = c[x];
        v = 0;
        for (i = 1; i <= n; ++i) {
            v += cx[i];
            a[i] = v > 0;
            cnt1[i] = cnt1[i - 1] + !a[i];
            ans[i] += (!a[i]) << x;
        }
        for (Cond *co = &conds[x].front(); co && co <= &conds[x].back(); ++co) {
            if (cnt1[co->r] - cnt1[(co->l) - 1] < 1) {
                puts("No");
                return 0;
            }
        }
    }
    puts("Yes");
    for (i = 1; i <= n; ++i)
        printf("%d%c", ans[i], (i < n) ? ' ' : '\n');

    return 0;
}
