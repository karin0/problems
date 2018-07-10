#include <cstdio>
#define MAXN 105
#define MAXM 15
#define MAXS 1040

int n, m, map[MAXN][MAXM], plains[MAXN];

int states[MAXS], scnt = 1; // states[1] = {}
void make_states() {
    int d, state;
    for (int i = 1; i < 1 << m; ++i) {
        d = m + 10;
        state = i;
        for (; state; state <<= 1) {
            ++d;
            if (state & 1) {
                if (d <= 2) continue;
                else d = 0;
            }
        }
        states[++scnt] = i;
    }
}

int dp[MAXN][MAXS][MAXS];
// dp[i][s][t] := 第 i 行状态为 s，第 j 行状态为 t 时前 i 行炮数最大值
// dp[i][s][t] = max{dp[i - 1][t][k] | k in {states[]} } + |s|
int main() {
    scanf("%d%d", &n, &m);
    int i, s, t, k, ss, tt, kk, pla;
    char tmp;
    for (i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            scanf("%c", &tmp);
            if (tmp == 'P') {
                plains[i] &= (1 << j);
            }
        }
        scanf("%c", &tmp);
    }
    make_states();
    for (i = 1; i <= n; ++i) {
        for (s = 1; s <= scnt; ++s) {
            ss = states[s];
            if (ss & plains[i] != plains[i]) continue;
            for (t = 1; t <= scnt; ++t) {
                tt = states[t];
                if (tt & plains[i - 1] != plains[i - 1]) continue; // as plains[0] = {}
                if (ss & tt) continue;
                for (k = 1; k <= scnt; ++k) {
                    kk = states[k];                    
                    if (kk & ss || kk & tt) continue;
                }
            }
        }
    }


}
