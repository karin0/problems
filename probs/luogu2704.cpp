#include <cstdio>
#include <algorithm>
#define MAXN 105
#define MAXM 15
#define MAXS 1040


void print_bin(int s) {
    for (int i = 31; i >= 0; --i) {
        printf("%d", (s >> i) & 1);
    }
    printf("\n");
}


int count(int s) {
    int res = 0;
    for (; s; s >>= 1)
        if (s & 1) ++res;
    return res;
}
int n, m, map[MAXN][MAXM], plains[MAXN];

int states[MAXS], scnt = 1; // states[1] = {}
void make_states() {
    int d, state;
    for (int i = 2; i < (1 << (m + 1)); i += 2) {
        d = m + 10;
        state = i;
        for (; state; state >>= 1) {
            ++d;
            if (state & 1) {
                if (d <= 2) goto tag;
                else d = 0;
            }
        }
        states[++scnt] = i;
        tag:;
    }
}


int dp[MAXN][MAXS][MAXS];
// dp[i][s][t] := 第 i 行状态为 s，第 j 行状态为 t 时前 i 行炮数最大值
// dp[i][s][t] = max{dp[i - 1][t][k] | k in {states[]} } + |s|
int main() {
    scanf("%d%d", &n, &m);
    int i, s, t, k, ss, tt, kk;
    int tmp, ans = 0;
    char line[MAXM];
    for (i = 1; i <= n; ++i) {
        scanf("%s", line);
        for (int j = 1; j <= m; ++j) {
            tmp = line[j - 1];
            if (tmp == 'P') {
                plains[i] |= (1 << j);
            }
        }
    }
    make_states();
    for (i = 1; i <= n; ++i) {
        for (s = 1; s <= scnt; ++s) {
            ss = states[s];
            if ((ss | plains[i]) != plains[i]) continue;
            for (t = 1; t <= scnt; ++t) {
                tt = states[t];
                if ((tt | plains[i - 1]) != plains[i - 1]) continue; // as plains[0] = {}
                if (ss & tt) continue;
                for (k = 1; k <= scnt; ++k) {
                    kk = states[k];
                    tmp = plains[((i - 2) >= 0) ? (i - 2) : (i - 1)];
                    if ((kk | tmp) != tmp) continue;
                    if ((kk & ss) || (kk & tt)) continue;
                    dp[i][s][t] = std::max(dp[i][s][t], dp[i - 1][t][k] + count(s));
                    if (i == n) ans = std::max(ans, dp[i][s][t]);
                }
            }
        }
    }
    printf("%d\n", ans);


}
