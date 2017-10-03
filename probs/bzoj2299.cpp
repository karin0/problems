#include <cstdio>

typedef long long ll;

ll g;
inline void exgcd(ll a, ll b, ll &x, ll &y) {
    if (b)
        exgcd(b, a % b, y, x), y -= x * (a / b);
    else
        g = a, x = 1, y = 0;
}
inline bool check_solution(ll p1, ll q1, ll p2, ll q2) {
    return ((p1 & 1) == (q2 & 1)) && ((p2 & 1) == (q1 & 1));
}
inline bool solve(ll a, ll b, ll n, ll m) {
    static ll p1, q1, p2, q2, a1, b1, a2, b2;
    exgcd(a, b, p1, q1);
    if (n % g)
        return false;
    a1 = a / g, b1 = b / g;
    p1 *= n / g, q1 *= n / g;
    exgcd(a, b, p2, q2);
    if (m % g)
        return false;
    a2 = a / g, b2 = b / g;
    p2 *= m / g, q2 *= m / g;
    return     check_solution(p1, q1, p2, q2)
            || check_solution(p1 - b1, q1 + a1, p2, q2)
            || check_solution(p1, q1, p2 - b2, q2 + a2)
            || check_solution(p1 - b1, q1 + a1, p2 - b2, q2 + a2);
}

int main() {
    static int t, ks;
    static ll a, b, n, m;
    scanf("%d", &t);
    for (ks = 0; ks < t; ++ks) {
        scanf("%lld%lld%lld%lld", &a, &b, &n, &m);
        puts(solve(a, b, n, m) ? "Y" : "N");
    }

    return 0;
}
