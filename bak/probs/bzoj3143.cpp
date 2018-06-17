#include <cmath>
#include <cstdio>
#include <algorithm>
#include <vector>

const int MAXN = 505, MAXM = 250005;

int n, m;
std::vector<int> di[MAXN];
struct Edge {
    int u, v;
} se[MAXM];

namespace Gauss {
    double a[MAXN][MAXN];
    
    inline void solve() {
        int i, j, k, c;
        for (i = 0; i < n; ++i) {
            c = i;
            for (j = i + 1; j < n; ++j)
                if (fabs(a[j][i]) > fabs(a[c][i]))
                    c = j;
            if (c != i)
                for (j = i; j <= n; ++j)
                    std::swap(a[c][j], a[i][j]);
            for (j = 0; j < n; ++j)
                if (i != j)
                    for (k = n; k >= i; --k)
                        a[j][k] -= a[i][k] * a[j][i] / a[i][i];

        }
    }
    inline double ans(int x) {
        return a[x][n] / a[x][x];
    }
}

inline bool qaq(const Edge &x, const Edge &y) {
    return Gauss::ans(x.u) + Gauss::ans(x.v) > Gauss::ans(y.u) + Gauss::ans(y.v);
}


int main() {
    int i, u, v;
    double ans = 0.0;
    scanf("%d%d", &n, &m);
    for (i = 0; i < m; ++i) {
        scanf("%d%d", &u, &v);
        --u, --v;
        // if (u > v)
        //     std::swap(u, v);
        di[u].push_back(v), di[v].push_back(u);
        se[i].u = u, se[i].v = v;
    }
    
    for (i = 0; i < n - 1; ++i) {
        Gauss::a[i][i] = -((double)(di[i].size()));
        // Gauss::a[i][n] = 0.0;
        for (int *p = &di[i].front(); p && p <= &di[i].back(); ++p)
            Gauss::a[i][*p] = 1.0;
    }
    Gauss::a[0][n] = -1.0;
    Gauss::a[n - 1][n - 1] = 1.0;
    Gauss::solve();

    std::sort(se, se + m, qaq);

    for (i = 0; i < m; ++i) {
        ans += (Gauss::ans(se[i].u) + Gauss::ans(se[i].v)) * (i + 1);
    }
    printf("%.3lf", ans);

    return 0;
}
