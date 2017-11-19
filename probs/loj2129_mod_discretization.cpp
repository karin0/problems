#include <cstdio>
#include <algorithm>

const int MAXN = 2 * 1e6 + 10;
const int MAXM = 1e6 + 5;
const int MOD = 101377;

namespace DS {
    int n, fa[MAXN];
    inline void init() {
        for (int i = 1; i <= n; ++i)
            fa[i] = i;
    }
    inline int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
    inline void merge(int x, int y) {
        fa[find(x)] = find(y);
    }
    inline bool same(int x, int y) {
        return find(x) == find(y);
    }
}

struct Query {
    int x, y, c;
} qwq[MAXM];

inline void read(int &res) {
    res = 0;
    char ch = 0;
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9')
        res = res * 10 + ch - '0', ch = getchar();
}

int main() {
    int t, n, i, x, y, c;
    bool fail;
    read(t);
    while (t--) {
        read(n);
        for (i = 1; i <= n; ++i) {
            read(x), read(y), read(c);
            qwq[i].x = x % MOD, qwq[i].y = y % MOD, qwq[i].c = c;
        }
        DS::n = MOD;
        DS::init();
        for (i = 1; i <= n; ++i) {
            const Query &qaq = qwq[i];
            if (qaq.c == 1)
                DS::merge(qaq.x, qaq.y);
        }
        fail = false;
        for (i = 1; i <= n; ++i) {
            const Query &qaq = qwq[i];
            if (qaq.c == 0 && DS::same(qaq.x, qaq.y)) {
                fail = true;
                break;
            }
        }
        printf(fail ? "NO\n" : "YES\n");
    }

    return 0;
}
