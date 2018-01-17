#include <cstdio>
#include <algorithm>

typedef long long ll;
const int N = 103, M = 1000005, L = 10005, INF = 0x7f7f7f7f;
// const int P = 3, p[3] = {2017, 1000000007, 1000000009};
const int P = 2, p[3] = {21893, 18341629}; // orz Pepcy_Ch
int n, a[N], roots[M], rcnt, ans;
char s[N][L];
void init(int mo) {
    static int i, sgn;
    static char *c;
    for (i = 0; i <= n; ++i) {
        a[i] = 0;
        sgn = 1;
        c = s[i] + 0;
        if (*c == '-')
            ++c, sgn = -1;
        for (; *c; ++c)
            a[i] = ((ll)a[i] * 10 % mo + (*c - '0')) % mo;
        a[i] *= sgn;
        // printf("Modded %d, a[%d] is %d\n", mo, i, a[i]);
    }
}
bool check(int x, int mo) {
    static int y, i;
    for (y = 0, i = n; i >= 0; --i)
        y = ((ll)y * x % mo + a[i]) % mo;
    return y == 0;
}
int main() {
    static int m, i, j, x;
    scanf("%d%d", &n, &m);
    for (i = 0; i <= n; ++i)
        scanf("%s", s[i]);
    init(p[0]);
    for (i = 0; i < p[0]; ++i)
        if (check(i, p[0]))
            for (j = 0; (x = j * p[0] + i) <= m; ++j)
                if (x != 0)
                    roots[++rcnt] = x;
    ans = rcnt;
    for (i = 1; i < P; ++i) {
        init(p[i]);
        for (j = 1; j <= rcnt; ++j)
            if (roots[j] != INF && !check(roots[j], p[i]))
                roots[j] = INF, --ans;
    }
    std::sort(roots + 1, roots + rcnt + 1);
    printf("%d\n", ans);
    for (i = 1; i <= ans; ++i)
        printf("%d\n", roots[i]);
    return 0;
}
