#include <cstdio>
#include <algorithm>

const int MAXN = 200005, INF = 2147483600;

int n, cnt = 1, lind[MAXN], rind[MAXN];
struct Item {
    int val, ind;
} a[MAXN];
inline bool operator < (const Item &x, const Item &y) {
    return (x.val == y.val) ? (x.ind < y.ind) : (x.val < y.val);
}

int main() {
    int i, ans, stage,  prev;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i)
        scanf("%d", &a[i].val), a[i].ind = i;
    
    std::sort(a + 1, a + n + 1);
    lind[1] = a[1].ind;
    for (i = 2; i <= n; ++i)
        if (a[i].val != a[i - 1].val) {
            rind[cnt] = a[i - 1].ind;
            lind[++cnt] = a[i].ind;
        }
    rind[cnt] = a[n].ind;

    stage = 1;
    ans = 0;
    prev = INF;
    for (i = 1; i <= cnt; ++i) {
        if (stage == -1) {
            if (prev > rind[i])
                prev = lind[i];
            else
                prev = rind[i], stage = 1;
        } else {
            if (prev < lind[i])
                prev = rind[i];
            else
                stage = -1, ++ans, prev = lind[i];
        }
    }
    
    printf("%d\n", ans);
    return 0;
}
