#include <algorithm>
#include <vector>
#include <akari>

IO<1000000, 1000000> io;

cint N = 100002;

std::vector<int> g[10];
int deg[10];
bool vis[10];

inline bool cmp(int i, int j) {
    return deg[i] > deg[j];
}

bool ff[8][8], us[8][8];
inline bool &f(int i, int j) {
    if (i > j)
        return ff[j][i];
    return ff[i][j];
}
inline bool &used(int i, int j) {
    if (i > j)
        return us[j][i];
    return us[i][j];
}
int cnt[10];

int ans, det[10];
void dfs(int u) {
    if (ans >= 21)
        return;
    vis[u] = true;
    std::sort(g[u].begin(), g[u].end(), cmp);
    int &t = det[u];
    for (int v : g[u]) {
        if (u && !used(u, v)) {
            if (det[v]) {
                if (!t) {
                    rep (i, 1, 6) if (cnt[i] && !f(i, det[v]))  { // && (!t || cnt[i] > cnt[t]))
                        t = i;
                        break;
                    }
                    // t = std::max_element(cnt + 1, cnt + 6 + 1) - cnt;
                }
                if (cnt[t] && !f(t, det[v])) {
                    used(u, v) = true;
                    --deg[v];
                    int i = det[v];
                    f(t, i) = true;
                    --cnt[t];
                    --cnt[i];
                    // ccc(u, v, t, i);
                    ++ans;
                    break;
                }
            } else {
                if (!t) {

                    rep (i, 1, 6) if (cnt[i]) {
                       t = i;
                       break;
                    }
                    // t = std::max_element(cnt + 1, cnt + 6 + 1) - cnt;
                }
                if (cnt[t]) {
                    rep (i, 1, 6) if (!f(t, i)) {
                        used(u, v) = true;
                        --deg[v];
                        f(t, i) = true;
                        --cnt[t];
                        --cnt[i];
                        det[v] = i;
                        // ccc(u, v, t, i);
                        ++ans;
                        break;
                    }
                }
            }
        }
        if (!vis[v])
            dfs(v);
    }
}

int main() {
    rep (i, 1, 6)
        cnt[i] = 6;

    int n, m;
    io >> n >> m;
    while (m--) {
        int u, v;
        io >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
        ++deg[u];
        ++deg[v];
    }
    rep (i, 1, n)
        g[0].push_back(i);
    dfs(0);
    io << ans daze;
}
