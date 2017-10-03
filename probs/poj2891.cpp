#include <cstdio>

typedef long long ll;
const int MAXN = 100005;

int n;
ll g;
inline void exgcd(ll a, ll b, ll &x, ll &y) {
    b ? (exgcd(b, a % b, y, x), y -= (a / b) * x) : (g = a, x = 1, y = 0);
}

struct Equ {
    ll m, a;
} equs[MAXN];
inline ll solve() {
    static ll mm = equs[1].m, aa = equs[1].a, k1, k2, i;
    for (i = 2; i <= n; ++i) {
        const Equ &eq = equs[i];
        exgcd(mm, eq.m, k1, k2);
        if ((aa - eq.a) % g != 0)
            return -1;
        k1 = ((aa - eq.a) / g * k1);
        aa = (aa - k1 * mm);
        mm = mm / g * eq.a;
    }
    return (aa % mm + mm) % mm;
}

int main() {
    int i;
    while (scanf("%d", &n) == 1) {
        for (i = 1; i <= n; ++i)
            scanf("%lld%lld", &equs[i].m, &equs[i].a);
        printf("%lld\n", solve());
    }
    return 0;
}
