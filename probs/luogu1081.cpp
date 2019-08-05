#include <cstdio>
#include <cmath>
#include <algorithm>

typedef long long ll;
const int MAXN = 100005, MAXM = 100005;
const double EPS = 1e-7, INF = 1e14;
int n, h[MAXN];
inline bool cmp(const int a, const int b) {
    return h[a] < h[b];
}
int arr[MAXN], next[MAXN], prev[MAXN];
int dist(int a, int b) {
    if (a < 0 || a > n || b < 0 || b > n)
        return 0;
    return std::abs(h[a] - h[b]);
}
int next_a[MAXN], next_b[MAXN], jmp[MAXN][20];
ll dis_a[MAXN][20], dis_b[MAXN][20];

int lbn, res_a, res_b;
void travel(int pos, int x) {
    static int j, np;
    static long long nd, d;
    res_a = 0;
    res_b = 0;
    if (x == 0)
        return;
    d = 0;
    for (j = lbn; j >= 0; --j) {
        if (pos == n)
            break;
        // printf("j = %d, arrived %d, went %lld\n", j, pos, d);
        np = jmp[pos][j];
        if (!np) {
            // puts("Gone over");
            continue;
        }
        nd = d + dis_a[pos][j] + dis_b[pos][j];
        if (nd > x) {
            // puts("Too far");
            continue;
        }
        d = nd;
        res_a += dis_a[pos][j];
        res_b += dis_b[pos][j];
        pos = np; // This must be the last to do
        // printf("Success reached %d\n", pos);
    }
    // res_a = d - res_b;
    nd = dist(next_a[pos], pos);
    if (next_a[pos] && d + nd <= x)
        res_a += nd;
}
int main() {
    static int m, i, j, d1, d2, x, da, dd;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d", h + i);
        arr[i] = i;
    }
    scanf("%d", &x);
    std::sort(arr + 1, arr + n + 1, cmp);
    for (i = 1; i <= n; ++i) {
        prev[arr[i]] = arr[i - 1];
        next[arr[i]] = arr[i + 1];
        // printf("prev[%d] = %d, next[%d] = %d\n", arr[i], prev[arr[i]], arr[i], next[arr[i]]);
    }
    for (i = 1; i <= n; ++i) {
        if (prev[i] == 0){
            next_b[i] = next[i];
            next_a[i] = next[next[i]];
        } else if (next[i] == 0) {
            // printf("%d no next\n", i);
            next_b[i] = prev[i];
            next_a[i] = prev[prev[i]];
        } else {
            d1 = h[i] - h[prev[i]];
            d2 = h[next[i]] - h[i];
            if (d1 <= d2) {
                // printf("%d to left\n", i);
                next_b[i] = prev[i];
                next_a[i] = next[i];
                dd = h[i] - h[prev[prev[i]]];
                if (prev[prev[i]] && dd <= d2)
                    next_a[i] = prev[prev[i]], da = dd;
            } else {
                next_b[i] = next[i];
                next_a[i] = prev[i];
                dd = h[next[next[i]]] - h[i];
                if (next[next[i]] && dd < d1)
                    next_a[i] = next[next[i]];
            }
        }
        prev[next[i]] = prev[i];
        next[prev[i]] = next[i];
    }
    next_a[n] = next_b[n] = 0; // **
    for (i = 1; i <= n; ++i) {
        // printf("nexta[%d] = %d, nextb[%d] = %d\n", i, next_a[i], i, next_b[i]);
        jmp[i][0] = next_b[next_a[i]];
        dis_a[i][0] = dist(i, next_a[i]);
        dis_b[i][0] = dist(next_a[i], next_b[next_a[i]]);
        // printf("jmp[%d][%d] = %d\n", i, 0, jmp[i][0]);
        // printf("dis_a[%d][%d] = %lld\n", i, 0, dis_a[i][0]);
        // printf("dis_b[%d][%d] = %lld\n", i, 0, dis_b[i][0]);
    }
    for (j = 1; (1 << j) <= n; ++j) {
        for (i = 1; i + (1 << (j - 1)) - 1 <= n; ++i) {
            jmp[i][j] = jmp[jmp[i][j - 1]][j - 1];
            dis_a[i][j] = dis_a[i][j - 1] + dis_a[jmp[i][j - 1]][j - 1];
            dis_b[i][j] = dis_b[i][j - 1] + dis_b[jmp[i][j - 1]][j - 1];
            // printf("jmp[%d][%d] = %d\n", i, j, jmp[i][j]);
            // printf("dis_a[%d][%d] = %lld\n", i, j, dis_a[i][j]);
            // printf("dis_b[%d][%d] = %lld\n", i, j, dis_b[i][j]);
        }
    }
    lbn = j - 1;
    static double ans, rat;
    static int s;
    ans = INF;
    for (i = 1; i <= n; ++i) {
        travel(i, x);
        // printf("Travels %d, %d makes %d, %d\n", i, x, res_a, res_b);
        if (res_a == 0)
            rat = 0;
        else if (res_b == 0)
            rat = INF;
        else
            rat = (double)res_a / res_b;
        if (fabs(rat - ans) <= EPS) {
            if (h[i] > h[s])
                s = i;
        } else if (rat < ans) {
            ans = rat;
            s = i;
        }
    }
    printf("%d\n", s);
    scanf("%d", &m);
    for (i = 1; i <= m; ++i) {
        scanf("%d%d", &s, &x);
        travel(s, x);
        printf("%d %d\n", res_a, res_b);
    }

    return 0;
}
