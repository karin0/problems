#include <cstdio>

const int MAXN = 33, MAXM = 23;
int n, m, p, ans;
int det[MAXM];
bool used[MAXN];

void dfs(int i) {
    int j;
    if (i > n) {
        ++ans;
        if (ans >= p)
            ans -= p;
    } else if (det[i]) {
        for (j = det[i]; j <= n; ++j) {
            if (!used[j]) {
                used[j] = true;
                dfs(i + 1);
                used[j] = false;
                break;
            }
        }
    } else {
        for (j = 1; j <= n; ++j) {
            if (!used[j]) {
                used[j] = true;
                dfs(i + 1);
                used[j] = false;
            }
        }
    }
}

int main() {
    static int i, x, y;
    scanf("%d%d%d", &n, &m, &p);
    for (i = 1; i <= m; ++i) {
        scanf("%d%d", &x, &y);
        det[x] = y;
    }
    dfs(1);
    printf("%d\n", ans);
    return 0;
}
