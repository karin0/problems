#include <cstdio>
#include <vector>

const int N = 1005;
std::vector<int> g[N];
int n, s, bcnt, cent[N], ssz, bel[N], sta[N];
void dfs(int u, int f) {
    int osz = ssz;
    for (std::vector<int>::iterator it = g[u].begin(); it != g[u].end(); ++it) {
        if (*it == f)
            continue;
        dfs(*it, u);
        if (ssz - osz >= s) {
            ++bcnt;
            while (ssz != osz)
                bel[sta[--ssz]] = bcnt;
            cent[bcnt] = u;
        }
    }
    sta[ssz++] = u;
}
void make() {
    dfs(1, 0);
    while (ssz)
        bel[sta[--ssz]] = bcnt;
}
int main() {
    static int i, u, v;
    scanf("%d%d", &n, &s);
    for (i = 1; i < n; ++i) {
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    make();
    printf("%d\n", bcnt);
    for (i = 1; i <= n; ++i)
        printf("%d ", bel[i]);
    putchar('\n');
    for (i = 1; i <= bcnt; ++i)
        printf("%d ", cent[i]);
    putchar('\n');

    return 0;
}
