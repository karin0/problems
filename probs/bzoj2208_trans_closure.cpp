#include <cstdio>
#include <bitset>

const int MAXN = 2005;

int n;
std::bitset<MAXN> g[MAXN];

inline void floyd() {
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            if (g[i][k])
                g[i] |= g[k];
}

char line[MAXN];
int main() {
    int u, v, ans = 0;
    scanf("%d", &n);
    for (u = 1; u <= n; ++u) {
        g[u].set(u);
        scanf("%s", line + 1);
        for (v = 1; v <= n; ++v) 
            if (line[v] == '1')
                g[u].set(v);
        }
    }
    floyd();

    for (u = 1; u <= n; ++u)
        ans += g[u].count();

    printf("%d\n", ans);
    return 0;
}
