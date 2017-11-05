#include <cstdio>
#include <cctype>
#include <algorithm>

typedef long long ll;
typedef __int128 lll;
const int MAXM = 100005;
const lll INF = (lll)1 << 122;
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
int main() {
    static int i, a0, a1, k, ks, j, ms, ss, l, ub1, ub2;
    static lll p, q, r, mv, sv;
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
        else if (a0 >= 0 && a1 >= 0) {
            if (a0 > a1)
                printf("%d %d\n", (s[m] == 1 && m > 1 && s[m - 1] == 0) ? 0 : s[m], (s[1] == 0 && s[2] == 1) ? 1 : s[1]);
            else
                printf("%d %d\n", s[m], s[1]);
        } else if (a0 <= 0 && a1 <= 0) {
            if (a0 < a1)
                printf("%d %d\n", (s[1] == 0 && s[2] == 1) ? 1 : s[1], (s[m] == 1 && m > 1 && s[m - 1] == 0) ? 0 : s[m]);
            else
                printf("%d %d\n", s[1], s[m]);
        } else {
            p = a0;
            q = a1;
            j = 1;
            mv = -INF;
            sv = INF;
            ms = s[1];
            ss = s[1];
            // printf("Inittt ms = %d, mv = %lld, ss = %d, sv = %lld\n", ms, mv, ss, sv);
            if (s[1] == 0) {
                if (p > mv)
                    mv = p, ms = 0; //  printf("%d, %lld is larger\n", ms, mv);
                if (p < sv)
                    sv = p, ss = 0; // printf("%d, %lld is smaller\n", ss, sv);
            }
            if (s[1] == 1 || s[2] == 1) {
                if (q > mv)
                    mv = q, ms = 1; //  printf("%d, %lld is larger\n", ms, mv);
                if (q < sv)
                    sv = q, ss = 1; // printf("%d, %lld is smaller\n", ss, sv);
            }
            // printf("Init ms = %d, mv = %lld, ss = %d, sv = %lld\n", ms, mv, ss, sv);
            while (s[j] < 2)
                ++j;
            ub1 = std::min(260, s[m]);
            for (i = 2; i <= ub1; ++i) {
                // printf("ms = %d, mv = %lld, ss = %d, sv = %lld\n", ms, mv, ss, sv);
                if (p >= 0 && q >= 0) {
                    // puts("Inc");
                    ub2 = std::min((i << 1) + 4, s[m]);
                    for (l = i; l <= ub2; ++l) {
                        r = k * q + p;
                        if (r > mv) {
                            ms = s[m];
                            break;
                        }
                        p = q;
                        q = r;
                    }
                    break;
                } else if (p <= 0 && q <= 0) {
                    // puts("Dec");
                    ub2 = std::min((i << 1) + 4, s[m]);
                    for (l = i; l <= ub2; ++l) {
                        r = k * q + p;
                        if (r < sv) {
                            ss = s[m];
                            break;
                        }
                        p = q;
                        q = r;
                    }
                    break;
                }
                r = k * q + p;
                // printf("[%d %lld]\n", i, r);
                p = q;
                q = r;
                while (s[j] < i && j <= m)
                    ++j;
                if (s[j] == i) {
                    if (r > mv)
                        mv = r, ms = i; //  printf("%d, %lld is larger\n", ms, mv);
                    if (r < sv)
                        sv = r, ss = i; // printf("%d, %lld is smaller\n", ss, sv);
                }
            }
            printf("%d %d\n", ms, ss);
        }
    }
    return 0;
}
