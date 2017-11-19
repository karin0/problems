#include <cstdio>

int n, m, s[13], a[35], t[13], ans;
struct Comp {
    int x, y; // x < y
} c[35];
void dfs(int i, int r) {
    if (i > m) {
        for (i = 1; i <= n; ++i)
            if (s[i] != t[i])
                return;
        ans += r;
        return;
    }
    int x = c[i].x, y = c[i].y;
    if ((s[x] > t[x] + 3 * (n - y + 1) || s[x] < t[x]) || (s[y] > t[y] + 3 * (n - x + 1) || s[y] < t[y]))
        return;
    if (y == n) {
        int d = s[x] - t[x];
        if (d == 1) {
            t[x] += 1, t[y] += 1;
            if (!((s[x] > t[x] + 3 * (n - y + 1) || s[x] < t[x]) || (s[y] > t[y] + 3 * (n - x + 1) || s[y] < t[y])))
                dfs(i + 1, r);
            t[x] -= 1, t[y] -= 1;
        } else if (d == 3) {
            t[x] += 3;
            if (!((s[x] > t[x] + 3 * (n - y + 1) || s[x] < t[x]) || (s[y] > t[y] + 3 * (n - x + 1) || s[y] < t[y])))
                dfs(i + 1, r);
            t[x] -= 3;
        } else if (d == 0) {
            t[y] += 3;
            if (!((s[x] > t[x] + 3 * (n - y + 1) || s[x] < t[x]) || (s[y] > t[y] + 3 * (n - x + 1) || s[y] < t[y])))
                dfs(i + 1, r);
            t[y] -= 3;
        }
        return;
    }
    t[x] += 1, t[y] += 1;
    if (!((s[x] > t[x] + 3 * (n - y + 1) || s[x] < t[x]) || (s[y] > t[y] + 3 * (n - x + 1) || s[y] < t[y])))
        dfs(i + 1, r);
    t[x] -= 1, t[y] -= 1;
    t[x] += 3;
    if (!((s[x] > t[x] + 3 * (n - y + 1) || s[x] < t[x]) || (s[y] > t[y] + 3 * (n - x + 1) || s[y] < t[y])))
        dfs(i + 1, r);
    t[x] -= 3;
    t[y] += 3;
    if (!((s[x] > t[x] + 3 * (n - y + 1) || s[x] < t[x]) || (s[y] > t[y] + 3 * (n - x + 1) || s[y] < t[y])))
        dfs(i + 1, r);
    t[y] -= 3;
}

int main() {
    static int i, j;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i)
        scanf("%d", s + i);
    for (i = 1; i <= n; ++i) {
        for (j = i + 1; j <= n; ++j) {
            c[++m].x = i;
            c[m].y = j;
        }
    }
    dfs(1, 1);
    printf("%d\n", ans);

    return 0;
}
