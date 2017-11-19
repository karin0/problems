#include <cstdio>
#include <algorithm>

const int MAXN = 1003;
int n, m, k, ans = 0x7f7f7f7f, a[MAXN][MAXN], fg[MAXN][MAXN], fl[MAXN][MAXN], rg[MAXN][MAXN], rl[MAXN][MAXN];

int mono[MAXN], hd, tl, *src;
void clear() {
    hd = 1, tl = 0;
}
void push_max(int x) {
    while (tl - hd + 1 > 0 && src[mono[tl]] <= src[x])
        --tl;
    mono[++tl] = x;
}
void push_min(int x) {
    while (tl - hd + 1 > 0 && src[mono[tl]] >= src[x])
        --tl;
    mono[++tl] = x;
}
int pop(int x) { // 下标 >= x - k + 1
    while (tl - hd + 1 > 0 && mono[hd] < x - k + 1)
        ++hd;
    return src[mono[hd]];
}
int main() {
    static int i, j, *fgi, *fli;
    scanf("%d%d%d", &n, &m, &k);
    for (i = 1; i <= n; ++i) {
        src = a[i];
        for (j = 1; j <= m; ++j)
            scanf("%d", src + j);
    }
    for (i = 1; i <= n; ++i) {
        src = a[i];
        clear();
        fgi = fg[i];
        for (j = 1; j <= m; ++j) {
            push_max(j);
            if (j >= k)
                fgi[j] = pop(j);
        }
        clear();
        fli = fl[i];
        for (j = 1; j <= m; ++j) {
            push_min(j);
            if (j >= k)
                fli[j] = pop(j);
        }
    }
    for (j = k; j <= m; ++j) {
        clear();
        for (i = 1; i <= n; ++i) {
            while (tl - hd + 1 > 0 && fg[mono[tl]][j] <= fg[i][j])
                --tl;
            mono[++tl] = i;
            if (i >= k) {
                while (tl - hd + 1 > 0 && mono[hd] < i - k + 1)
                    ++hd;
                rg[i][j] = fg[mono[hd]][j];
            }
        }
        clear();
        for (i = 1; i <= n; ++i) {
            while (tl - hd + 1 > 0 && fl[mono[tl]][j] >= fl[i][j])
                --tl;
            mono[++tl] = i;
            if (i >= k) {
                while (tl - hd + 1 > 0 && mono[hd] < i - k + 1)
                    ++hd;
                rl[i][j] = fl[mono[hd]][j];
            }
        }
    }
    for (i = k; i <= n; ++i)
        for (j = k; j <= m; ++j)
            ans = std::min(ans, rg[i][j] - rl[i][j]);
    printf("%d\n", ans);
    return 0;
}
