#include <cstdio>

typedef long long ll;
const int MAXN = 10000005;

int n, f[MAXN];
// 我的意思已经很明显了
int pri[MAXN], pcnt;
bool np[MAXN];
void sieve_euler() {
    static int i, j;
    static ll v;
    np[0] = np[1] = true;
    for (i = 2; i <= n; ++i) {
        if (!np[i])
            pri[++pcnt] = i;
        for (j = 1; j <= pcnt; ++j) {
            v = (ll)i * pri[j];
            if (v > n)
                break;
            np[v] = true;
            if (i % pri[j] == 0)
                break;
        }
    }
}

int main() {
    static int m, i, l, r;
    scanf("%d%d", &m, &n);
    sieve_euler();
    for (i = 2; i <= n; ++i)
        f[i] = f[i - 1] + !np[i];
    for (i = 1; i <= m; ++i) {
        scanf("%d%d", &l, &r);
        if (1 <= l && l <= n && 1 <= r && r <= n)
            printf("%d\n", f[r] - f[l - 1]);
        else
            puts("Crossing the line");
    }

    return 0;
}
