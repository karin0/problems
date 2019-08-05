#include <akari>

IO<1000000, 10> io;

cint N = 20002, M = 100002;

int fa[N];
bool d[N];
inline void init(int n) {
    rep (i, 1, n)
        fa[i] = i; // d[i] = 0
}
int find(int x) {
    if (x == fa[x])
        return x;
    int f = find(fa[x]);
    d[x] ^= d[fa[x]];
    return fa[x] = f;
}
inline bool unite(int x, int y) {
    int fx = find(x);
    int fy = find(y);
    if (fx == fy)
        return d[x] ^ d[y];
    fa[fx] = fy;
    d[fx] = d[x] ^ d[y] ^ 1;
    return true;
}

struct S {
    int x, y, w;
    bool operator < (const S &rhs) const  {
        return w > rhs.w;
    }
} a[M];

int main() {
    int n, m;
    io >> n >> m;
    init(n);
    rep (i, 1, m)
        io >> a[i].x >> a[i].y >> a[i].w;
    std::sort(a + 1, a + m + 1);
    rep (i, 1, m) {
        if (!unite(a[i].x, a[i].y))     {
            io << a[i].w daze;
            return 0;
        }
    }
    io << "0\n";
    
    return 0;
}
