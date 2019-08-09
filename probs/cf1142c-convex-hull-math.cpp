#include <akari>

IO<1000000, 10> io;

cint N = 100002;

#define x first
#define y second
typedef std::pair<int, ll> S;

S a[N], c[N];
ll operator * (const S &p, const S &q) {
    return p.x * q.y - p.y * q.x;
}
S operator - (const S &p, const S &q) {
    return std::make_pair(p.x - q.x, p.y - q.y);
}

int main() {
    int n;
    io >> n;
    rep (i, 1, n) {
        S &p = a[i];
        io >> p.x >> p.y;
        p.y -= (ll)p.x * p.x;
    }

    std::sort(a + 1, a + n + 1);
    int an = 0, cn = 0;
    re (i, 1, n)
        if (a[i].x != a[i + 1].x)
            a[++an] = a[i];
    a[++an] = a[n];

    rep (i, 1, an) {
        while (cn > 1 && (c[cn] - c[cn - 1]) * (a[i] - c[cn - 1]) >= 0)
            --cn;
        c[++cn] = a[i];
    }

    io << cn - 1 daze;


    return 0;
}
