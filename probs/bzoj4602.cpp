#include <cstdio>
#include <cmath>
#include <algorithm>

const int MAXN = 10005;
const double EPS = 1e-8;
// typedef long long ll;
/*
inline ll gcd(ll x, ll y) {
    return y ? gcd(y, x % y) : x;
}*/
int n;
int fa[MAXN];
/*
struct Rat {
    ll u, v;
    Rat (ll x, ll y) {
        if (x < 0)
            x = -x, y = -y;
        ll g = gcd(x, std::abs(y));
        u = x / g, v = y / g;
    }
    Rat (): u(1), v(1) {}
};
Rat r[MAXN];
Rat operator * (const Rat &x, const Rat &y) {
    return Rat(x.u * y.u, x.v * y.v); 
}
Rat rec(const Rat &x) {
    return Rat(x.v, x.u);
}
Rat operator / (const Rat &x, const Rat &y) {
    return x * rec(y);
}
bool operator == (const Rat &x, const Rat &y) {
    return x.u == y.u && x.v == y.v;
}
*/
long double r[MAXN];
inline void init() {
    for (int i = 0; i <= n; ++i)
        fa[i] = i, r[i] = (long double)1.0;
}
inline int find(int x) {
    int f = fa[x]; // Never use a static one
    if (f == x)
        return x;
    fa[x] = find(f);
    r[x] = r[x] * r[f];
    // printf("[%d, %d, %lld / %lld]\n", x, fa[x], r[x].u, r[x].v);
    return fa[x];
}
inline bool merge(int x, int y, int u, int v) {
    int fx = find(x), fy = find(y);
    if (fx == fy)
         //printf("[%d, %d, %d, %lld / %lld, %lld / %lld]\n", x, y, fx, a.u, a.v, b.u, b.v);
        // return fabs(v * r[y] - r[x]) <= EPS;
        return fabs((u * r[y]) - (v * r[x])) <= EPS;
    fa[fx] = fy;
    r[fx] = (u * r[y]) / (v * r[x]);
    // printf("[%d, %d, %lld / %lld]\n", fx, fa[fx], r[fx]);
    return true;
}
/*
inline void pr(const Rat &x) {
    printf("{%lld / %lld}\n", x.u, x.v);
}*/

int main() {
    // if (Rat(-25, 3) == Rat(50, -6))
    //    puts("2333");
    int t, kase, m, i, u, v, x, y;
    bool suc;
    scanf("%d", &t);
    for (kase = 1; kase <= t; ++kase) {
        scanf("%d%d", &n, &m);
        suc = true;
        init();
        for (i = 1; i <= m; ++i) {
            scanf("%d%d%d%d", &u, &v, &x, &y);
            if (suc)
                //suc = merge(u, v, Rat(x, y));
                suc = merge(u, v, x, y);
        }
        printf(suc ? "Case #%d: Yes\n" : "Case #%d: No\n", kase);
    }

    return 0;
}
