#include <cstdio>
#include <cctype>
#include <algorithm>

typedef long long ll;
const int MAXM = 100005;
const ll INF = (ll)1 << 62;
int n, m, s[MAXM];

inline void read(int &x) {
    char ch = 0;
    int sgn = 1;
    x = 0;
    while (ch != '-' && !isdigit(ch))
        ch = getchar();
    if (ch == '-')
        sgn = -1, ch = getchar();
    while (isdigit(ch)) {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    x *= sgn;
}
int min_i, max_i;
ll min_v, max_v;
void upd(ll v, int i) {
    if (v > max_v)
        max_v = v, max_i = i;
    if (v < min_v)
        min_v = v, min_i = i;
}
int main() {
    static int i, a0, a1, k, ks, cur;
    static ll p, q, r;
    read(m);
    for (i = 1; i <= m; ++i)
        read(s[i]);
    read(n);
    for (ks = 1; ks <= n; ++ks) {
        read(a0);
        read(a1);
        read(k);
        if (a0 == 0 && a1 == 0)
            printf("%d %d\n", s[1], s[1]);
        else {
            p = a0;
            q = a1;
            max_v = -INF;
            min_v = INF;
            max_i = s[1];
            min_i = s[1];
            cur = 1;
            if (s[cur] == 0)
                upd(p, 0);
            while (s[cur] < 1 && cur <= m)
                ++cur;
            if (s[cur] == 1)
                upd(q, 1);
            for (i = 2; ; ++i) {
                while (s[cur] < i && cur <= m)
                    ++cur;
                if (cur > m)
                    break;
                r = k * q + p;
                p = q;
                q = r;
                // printf("a_%d = %lld\n", i, q);
                if (p > 0 && q > 0 && p < q && q > max_v) { // Shouldn't include its equaling to 0
                    max_i = s[m];
                    break;
                }
                if (p < 0 && q < 0 && p > q && q < min_v) {
                    min_i = s[m];
                    break;
                }
                if (s[cur] == i)
                    upd(q, i);
            }
            printf("%d %d\n", max_i, min_i);
        }
    }
    return 0;
}
