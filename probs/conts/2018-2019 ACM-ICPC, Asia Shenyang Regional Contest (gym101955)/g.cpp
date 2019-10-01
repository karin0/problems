#include <akari>
#include <cstring>
#include <cmath>
#include <vector>

IO<1000000, 1000000> io;
cint L = 6000, K = 10000000, Q = 3163, Z = 200003;

int a[L + 1][L + 1];
std::vector<std::pair<int, int> > vec[K];
std::pair<int, int> toc[Z];

void iter(int x, int y, int k, void f(int, int)) {
#define F(i, j) if (i >= 1 && i <= L && j >= 1 && j <= L) f(i, j);
    ccc(x, y, k);
    if (!k)
        return f(x, y);
    int s = round(sqrt(k));
    if (s * s == k) {
        F(x - s, y);
        F(x + s, y);
        F(x, y - s);
        F(x, y + s);
    }
    s = round(sqrt(k / 2.0));
    if ((s * s << 1) == k) {
        F(x - s, y - s);
        F(x - s, y + s);
        F(x + s, y - s);
        F(x + s, y + s);
    }
    for (auto &t : vec[k]) {
        int i = t.first, j = t.second;
        F(x - i, y - j);
        F(x - i, y + j);
        F(x + i, y - j);
        F(x + i, y + j);
        F(x - j, y - i);
        F(x - j, y + i);
        F(x + j, y - i);
        F(x + j, y + i);
    }
    /*
    // double z = sqrt(k / 2.0);
    s = sqrt(k / 2.0);
    rep (i, 1, s) {
        int t = k - i * i;
        int j = round(sqrt(t));
        if (i < j && j * j == t) {
            F(x - i, y - j);
            F(x - i, y + j);
            F(x + i, y - j);
            F(x + i, y + j);
            F(x - j, y - i);
            F(x - j, y + i);
            F(x + j, y - i);
            F(x + j, y + i);
        }
    }
    */
}

int qwq;
ll la;
inline void qry(int i, int j) {
    la += a[i][j];
}
inline void inc(int i, int j) {
    if (a[i][j])
        a[i][j] += qwq;
}

int main() {
    rep (i, 1, Q) {
        int t = i * i, s;
        for (int j = 1; j < i && (s = t + j * j) <= K; ++j)
            vec[s].push_back(std::make_pair(j, i));
    }

    int T;
    io >> T;
    for (int ks = 1; ; ++ks) {
        io << "Case #" << ks << ":\n";
        int n, m, x, y, k, cnt = 0;
        io >> n >> m;
        while (n--) {
            io >> x >> y >> k;
            a[x][y] = k;
            toc[++cnt] = std::make_pair(x, y);
        }
        la = 0;
        while (m--) {
            char op;
            io >> op >> x >> y;
            x = (x + la) % L + 1;
            y = (y + la) % L + 1;
            if (op == '2')
                a[x][y] = 0;
            else {
                io >> k;
                if (op == '1') {
                    a[x][y] = k;
                    toc[++cnt] = std::make_pair(x, y);
                } else if (op == '4') {
                    la = 0;
                    iter(x, y, k, qry);
                    io << la daze;
                } else {
                    io >> qwq;
                    iter(x, y, k, inc);
                }
            }
        }
        if (ks >= T)
            return 0;
        rep (i, 1, cnt)
            a[toc[i].first][toc[i].second] = 0;
    }
}
