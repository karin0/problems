#include <cstdio>

const int MAXN = 100005, MAXB = 31; // log2(1e9) = 29.90
struct Gate {
    int op, x; // 0 for OR, 1 for AND, 2 for XOR
} qwq[MAXN];
int n, m, h;
int test_bit(int x, int d) {
    static int op, a, i;
    for (i = 1; i <= n; ++i) {
        Gate &g = qwq[i];
        op = g.op, a = (g.x >> d) & 1; // ***
        if (op == 0)
            x |= a;
        else if (op == 1)
            x &= a;
        else
            x ^= a;
    }
    return x;
}
int make(int *a) {
    static int i, x;
    for (x = 0, i = 0; i < h; ++i)
        if (a[i])
            x += 1 << i;
    return x;
}
int test_x(int x) {
    static int op, a, i;
    for (i = 1; i <= n; ++i) {
        Gate &g = qwq[i];
        op = g.op, a = g.x;
        if (op == 0)
            x |= a;
        else if (op == 1)
            x &= a;
        else
            x ^= a;
    }
    return x;
}
int main() {
    static int i, x, init[MAXB], res, li;
    static char s[10];
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i) {
        scanf("%s%d", s, &qwq[i].x);
        if (s[0] == 'O')
            qwq[i].op = 0;
        else if (s[0] == 'A')
            qwq[i].op = 1;
        else
            qwq[i].op = 2;
    }
    for (h = 0; (1 << h) <= m; ++h); // 初始不能为 1 之最低位
    for (i = 0; i < h; ++i)
        init[i] = !test_bit(0, i) && test_bit(1, i);
    while ((res = make(init)) > m)
        for (i = li; i < h; ++i)
            if (init[i]) {
                init[i] = 0;
                li = i + 1;
                break;
            }
    
    printf("%d\n", test_x(res));
    return 0;
}
