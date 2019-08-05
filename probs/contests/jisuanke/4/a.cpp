#include <cstdio>
#include <algorithm>

const int MAXN = 10000005, MAXM = 100005;

int n = 1;
struct Query {
    int l, r;
} qwq[MAXM];

int pri[MAXN], pcnt, f[MAXN];
bool notp[MAXN], iss[MAXN];
inline void shaker() {
    static int i, j;
    static long long v;
    notp[0] = notp[1] = true;
    for (i = 2; i <= n; ++i) {
        if (!notp[i])
            pri[++pcnt] = i;
        for (j = 1; j <= pcnt; ++j) {
            v = (long long)i * (long long)pri[j];
            if (v > n)
                break;
            notp[v] = true;
            if (i % pri[j] == 0)
                break;
        }
    }
    // int ccc = 0;
    for (i = 2; i <= n; ++i) {
        if (notp[i]) {
            for (j = 1; j <= pcnt && pri[j] <= i; ++j) {
                if (i % pri[j] == 0) {
                    if (!notp[i / pri[j]])
                        iss[i] = true;
                    break;
                }
            }
        }
    }
}


int main() {
    int i, m, l, r;
    n = MAXN - 2;
    shaker();
    for (i = 2; i <= n; ++i) {
        if ((!notp[i]) || iss[i])
            f[i] = f[i - 1] + 1;
        else
            f[i] = f[i - 1];
    }
    scanf("%d", &m);
    for (i = 1; i <= m; ++i) {
        scanf("%d%d", &l, &r);
        printf("%d\n", f[r] - f[l - 1]);
    
    }

    return 0;
}
