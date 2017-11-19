#include <cstdio>

typedef long long ll;
const int MAXN = 10000005;
int n, pri[MAXN], pcnt;
bool np[MAXN];
void sieve() {
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
    static int i, m, x;
    scanf("%d%d", &n, &m);
    sieve();
    for (i = 1; i <= m; ++i)
        scanf("%d", &x), puts(np[x] ? "No" : "Yes");

    return 0;
}
