#include <cstdio>
#include <algorithm>

const int MAXN = 2 * 1e6 + 10;
const int MAXM = 1e6 + 5;

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

struct Var {
    int id, q;
} vars[MAXN];
struct Query {
    int x, y, c;
} qwq[MAXM];
inline bool cmp_var(Var& x, Var& y) {
    return x.id < y.id;
}

inline void read(int &res) {
    res = 0;
    char ch = 0;
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9')
        res = res * 10 + ch - '0', ch = getchar();
}

int main() {
    int t, n, i, x, y, c, last_id, cnt_var;
    bool fail;
    read(t);
    while (t--) {
        read(n);
        for (i = 1; i <= n; ++i) {
            read(x), read(y), read(c);
            vars[i].id = x, vars[i].q = i;
            vars[n + i].id = y, vars[n + i].q = i;
            qwq[i].x = 0, qwq[i].y = 0, qwq[i].c = c;
        }
        std::sort(vars + 1, vars + n + n + 1, cmp_var);
        last_id = -1;
        cnt_var = 0;
        for (i = 1; i <= n + n; ++i) {
            const Var &var = vars[i];
            Query &qaq = qwq[var.q];
            (qaq.x ? qaq.y : qaq.x) = (var.id == last_id ? cnt_var : (last_id = var.id, ++cnt_var)); // 错误的压行姿势
        }
        DS::n = cnt_var;
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
