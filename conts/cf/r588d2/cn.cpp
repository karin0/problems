#include <algorithm>
#include <vector>
#include <akari>

IO<1000000, 1000000> io;

cint N = 100002;

struct Edge {
    int u, v;
} a[230];

bool ff[8][8];
inline bool &f(int i, int j) {
    if (i > j)
        return ff[j][i];
    return ff[i][j];
}

int n, m, ans, det[10];
void dfs(int u, int p) {
    det[u] = p;
    if (u >= n) {
        rep (i, 1, 6) rep (j, i, 6)
            f(i, j) = false;
        int cnt = 0;
        rep (i, 1, m) {
            bool &t = f(det[a[i].u], det[a[i].v]);
            if (!t)
                t = true, ++cnt;
        }
        ans = std::max(ans, cnt);
        return;
    }
    rep (i, 1, 6) // *** ????
        dfs(u + 1, i);
}

int main() {
    io >> n >> m;
    rep (i, 1, m)
        io >> a[i].u >> a[i].v;
    dfs(0, 1); // ****
    io << ans daze;
}
