#include <cstdio>
#include <cctype>
#include <algorithm>

typedef long long ll;
typedef __int128 lll;
const int MAXN = 1000005, MOD = 19260817;
int n, a[MAXN], arr[MAXN], rk[MOD + 3], vcnt;
inline void read(int &x) {
    char ch = 0;
    while (!isdigit(ch = getchar()));
    while (isdigit((x = x * 10 + (ch - '0'), ch = getchar())));
}
ll bit[MAXN];
inline int lowbit(int x) {
    return x & -x;
}
ll query(int o) {
    static ll res;
    for (res = 0; o >= 1; res += bit[o], o -= lowbit(o));
    return res;
}
void update(int o, int x) {
    for (; o <= vcnt; bit[o] += x, o += lowbit(o));
}
int main() {
    static int i;
    static lll ans;
    read(n);
    for (i = 1; i <= n; ++i)
        read(a[i]), arr[i] = a[i];
    std::sort(arr + 1, arr + n + 1);
    vcnt = std::unique(arr + 1, arr + n + 1) - arr - 1;
    /*for (i = 1; i <= vcnt; ++i) {
        while (rk[arr[i] % MOD]);
        rk[arr[i] % MOD] = i;
    }*/
    for (i = 1; i <= n; ++i) {
        // a[i] = rk[a[i] % MOD];
        a[i] = std::lower_bound(arr + 1, arr + vcnt + 1, a[i]) - arr;
        ans += (lll)(query(vcnt) - query(a[i])) * (n - i + 1);
        update(a[i], i);
    }

    static int tmp[10000], dcnt;
    while (ans)
        tmp[++dcnt] = ans % 10, ans /= 10;
    if (dcnt == 0)
        tmp[++dcnt] = 0;
    for (i = dcnt; i >= 1; --i)
        putchar('0' + tmp[i]);
    putchar('\n');
    return 0;
}
