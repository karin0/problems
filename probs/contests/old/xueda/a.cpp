#include <cstdio>

typedef long long ll;
const int MAXN = 100005;
int n;
ll gcd(ll x, ll y) {
    return y == 0 ? x : gcd(y, x % y);
}
ll a[MAXN], g;

int main() {
    static int i, m;
    static ll x;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i)
        scanf("%lld", a + i);
    g = a[1];
    for (i = 2; i <= n; ++i)
        g = gcd(g, a[i]);
    for (i = 1; i <= m; ++i) {
        scanf("%lld", &x);
        puts(((x & 1) || ((x >> 1) % g)) ? "No" : "Yes");
    }
    return 0;    
}
