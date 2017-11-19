#include <cstdio>
#include <algorithm>

const int MAXN = 50005;
int len, n, m, a[MAXN];
bool check(int x) {
    static int cnt, i, pos;
    cnt = 0;
    pos = 0;
    for (i = 1; i <= n; ++i) {
        if (a[i] - a[pos] < x) {
            ++cnt;
            if (cnt > m)
                return false;
        } else
            pos = i;
    }
    return true;
}

int main() {
    static int i, l, r, x;
    scanf("%d%d%d", &len, &n, &m);
    for (i = 1; i <= n; ++i) {
        scanf("%d", a + i);
        l = std::min(l, a[i] - a[i - 1]);
    }
    l = std::min(l, len - a[n]);
    a[++n] = len;
    r = len + 1;
    while (r - l > 1) {
        x = (l + r) >> 1;
        if (check(x))
            l = x;
        else
            r = x;
    }
    printf("%d\n", l);
    return 0;
}
