#include <akari>

IO<1000000, 1000000> io;

cint N = 30002;

int fa[N], siz[N], d[N];

int find(int u) {
    if (u == fa[u])
        return u;
    int f = find(fa[u]); // 根
    d[u] += d[fa[u]];
    return fa[u] = f;
}
inline void move(int u, int v) {
    u = find(u);
    v = find(v);
    d[u] = siz[v];
    siz[fa[u] = v] += siz[u];
}
inline int query(int u) {
    find(u);
    return d[u];
}

int main() {
    const int n = 30000;
    rep (i, 1, n)
        fa[i] = i, siz[i]= 1;
    int m = io;
    while (m--) {
        const char op = io;
        if (op == 'M') {
            int u = io;
            move(u, io);
        } else
            io << query(io) daze;
    }

    return 0;
}
