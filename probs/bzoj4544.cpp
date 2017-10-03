#include <cstdio>
#include <math.h>
#include <algorithm>

typedef long long ll;
const int P = 23;
const double EPS = 1e-6;

inline bool sq(ll x) {
    static ll sqr;
    if (x < 0)
        return false;
    sqr = round(sqrt(x));
    return sqr * sqr == x;
}
int pri[2000009], pcnt;
bool np[2000009];
inline void shaker(int x) {
    static int i, j;
    static ll v;
    // x = 1e7;
    np[0] = np[1] = true;
    for (i = 2; i <= x; ++i) {
        if (!np[i])
            pri[++pcnt] = i;
        for (j = 1; j <= pcnt; ++j) {
            v = (ll)pri[j] * i;
            if (v > x)
                break;
            np[v] = true;
            if (i % pri[j] == 0)
                break;
        }
    }

}
inline ll solve(ll r) {
    static int i, s, pos, pr, pc;
    static ll ub, rr, g, v, res, us, vt, p[P];
    static double t;
    res = 0;
    r <<= 1;
    rr = r;
    pc = 0;
    for (i = 1; i <= pcnt && (pr = pri[i], pr * pr <= rr); ++i) {
        if (rr % pr == 0) {
            if (i != 2) // *** g 不能有质因数 3
                p[++pc] = pr;
            while (rr % pr == 0)
                rr /= pr;
        }
    }
    if (rr != 1 && rr != 3)
        p[++pc] = rr; // printf("[%lld]", rr); // ****    
    for (i = (1 << pc) - 1; i >= 0; --i) {
        g = 1;
        for (s = i, pos = 1; s; s >>= 1, ++pos)
            if (s & 1)
                g *= p[pos];
        ub = r / g;
        for (v = 1; (vt = 3 * v * v) < ub; ++v) {
            us = ub - vt;
            if (sq(us))
                ++res;
        }

    }
    res <<= 2;
    r >>= 1;
    t = r / sqrt(3);
    if (fabs(t - round(t)) <= EPS)
        res += 2; // 这个啊
    return res + 2;
}

ll qwq[13];

int main() {
    static int t, i;
    static ll rmax;
    scanf("%d", &t);
    for (i = 1; i <= t; ++i)
        scanf("%lld", qwq + i), rmax = std::max(rmax, qwq[i]);
    shaker((int)sqrt(2 * rmax) + 1);
    for (i = 1; i <= t; ++i)
        printf("%lld\n", solve(qwq[i]));
    return 0;
}
