#include <cstdio>
#include <queue>
#include <algorithm>

const int MAXN = 200005;
int n, ind[MAXN], next[MAXN], ans = MAXN << 1;
bool vis[MAXN], rem[MAXN];
void dfs(int u, int dep) {
    vis[u] = true;
    if (rem[next[u]])
        return;
    if (vis[next[u]])
        ans = std::min(ans, dep + 1);
    else
        dfs(next[u], dep + 1);

}
std::queue<int> que;
int main() {
    static int i, u, v; 
    scanf("%d", &n);
    for (i = 1; i <= n; ++i)
        scanf("%d", &u), next[i] = u, ++ind[u];
    for (i = 1; i <= n; ++i)
        if (ind[i] == 0)
            que.push(i);
    while (!que.empty()) {
        u = que.front();
        que.pop();
        rem[u] = true;
        v = next[u];
        --ind[v];
        if (ind[v] == 0)
            que.push(v);
    }
    for (i = 1; i <= n; ++i)
        if (!rem[i] && !vis[i])
            dfs(i, 0);
    printf("%d\n", ans);
    return 0;
}
