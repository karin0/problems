#include <cstdio>
#include <cctype>

const int MAXN = 500005;
int n, a[MAXN];

inline int lowbit(int o) {
    return o & -o;
}
int bit[MAXN];
void update(int o, int x) {
    for (; o <= n; o += lowbit(o))
        bit[o] += x;
}
int query(int o) {
    static int res;
    for (res = 0; o >= 1; o -= lowbit(o))
        res += bit[o];
    return res;
}
void read(int &res) {
    static char ch;
    static bool neg;
    res = 0;
    ch = getchar();
    while (!(ch == '-' || isdigit(ch)))
        ch = getchar();
    neg = ch == '-';
    if (neg)
        ch = getchar();
    while (isdigit(ch))
        res = res * 10 + (ch - '0'), ch = getchar();
    if (neg)
        res = -res;
}

int main() {
    static int m, l, r, x, opt, i;
    read(n);
    read(m);
    for (i = 1; i <= n; ++i)
        read(a[i]);
    for (i = 1; i <= n; ++i)
        update(i, a[i] - a[i - 1]);
    for (i = 1; i <= m; ++i) {
        read(opt);
        read(l);
        if (opt == 1) {
            read(r);
            read(x);
            update(l, x);
            update(r + 1, -x);
        } else
            printf("%d\n", query(l));
    }

    return 0;
}
