#include <akari>

IO<1000000, 1000000> io;

cint N = 100002, M = 200002, siz = 1000;
uint tag[205][N], sum[N], key[N];
std::mt19937 rd(time(NULL));

struct Edge {
    int u, v, bel;
    void change() const {
        sum[u] ^= key[v];
        sum[v] ^= key[u];
    }
} g[M];

int main() {
    rep (i, 1, N - 2)
        key[i] = rd();
    int T = io;
    re (ks, 0, T) {
        int n, m;
        io >> n >> m;
        int bcnt = 1, bcur = 0;
        rep (i, 1, m) {
            Edge &e = g[i];
            if (++bcur > siz)
                bcur = 1, ++bcnt;
            e.bel = bcnt;
        }
        if (ks) {
            rep (i, 1, bcnt)
                rep (j, 0, n)
                    tag[i][j] = 0;
            rep (i, 1, n)
                sum[i] = 0;
        }
        rep (i, 1, m) {
            Edge &e = g[i];
            io >> e.u >> e.v;
            tag[e.bel][e.u] ^= key[e.v];
            tag[e.bel][e.v] ^= key[e.u];
        }
        int q = io;
        while (q--) {
            char op = io;
            int x, y;
            io >> x >> y;
            if (op == '1') {
                if (x > y)
                    std::swap(x, y); // ****
                Edge &ex = g[x], &ey = g[y];
                if (ex.bel == ey.bel) {
                    rep (i, x, y)
                        g[i].change();
                } else {
                    int t = siz * ex.bel;
                    rep (i, x, t)
                        g[i].change();
                    rep (i, siz * (ey.bel - 1) + 1, y)
                        g[i].change();
                    re (i, ex.bel + 1, ey.bel)
                        tag[i][0] ^= 1;
                }
            } else {
                uint sx = sum[x], sy = sum[y];
                rep (i, 1, bcnt) if (!tag[i][0]) {
                    sx ^= tag[i][x];
                    sy ^= tag[i][y];
                }
                io << char('0' + (sx == sy));
            }
        }
        io daze;
    }

    return 0;
}
