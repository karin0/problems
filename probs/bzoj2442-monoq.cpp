#include <cstdio>
#include <algorithm>

const int MAXN = 1000005;
typedef long long ll;
int n, k;

struct Item {
    int i;
    ll v;
} q[MAXN], *hd, *tl; // 递减
int main() {
    static int i, x;
    static ll s[MAXN], f, a;
    // freopen("mowlawn.in", "r", stdin);
    //freopen("mowlawn.out", "w", stdout);
    hd = q + 1, tl = q;
    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &x);
        s[i] = s[i - 1] + x;
    }
    *(++tl) = (Item){-1, 0}; // ***
    for (i = 0; ; ++i) { // 需要 i - 2 转移到 i 表示只取 i
        while (tl - hd + 1 > 0 && i - (hd->i + 2) + 1 > k)
            ++hd;
        f = hd->v + s[i];
        // printf("f[%d] = %lld, from %d\n", i, f, hd->i);
        if (i == n) {
            printf("%lld\n", f);
            return 0;
        }
        a = f - s[i + 1];
        while (tl - hd + 1 > 0 && tl->v < a)
            --tl;
        *(++tl) = (Item){i, a};
    }

    return 0;
}
