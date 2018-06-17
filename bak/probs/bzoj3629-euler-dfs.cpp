#include <cstdio>
#include <algorithm>

typedef long long ll;
const int N = 44734;
const int n = 44722;
int pri[N], pcnt;
bool np[N];
void sieve() {
    static int i, j;
    static ll v;
    for (i = 2; i <= n; ++i) {
        if (!np[i])
            pri[++pcnt] = i;
        for (j = 1; j <= pcnt && (v = (ll)i * pri[j]) <= n; ++j) {
            np[v] = true;
            if (i % pri[j] == 0)
                break;
        }
    }
}
int acnt, ans[N];
bool ispri(int x) {
    static int i;
    if (x <= n)
        return !(np[x] || x < 2);
    if ((x & 1) == 0)
        return false;
    for (i = 3; i * i <= x; i += 2)
        if (x % i == 0)
            return false;
    return true;
}
void dfs(ll x, ll s, int i) {
    if (s == 1) {
        ans[++acnt] = x;
        return;
    }
    if (pri[i] <= s - 1 && ispri(s - 1)) {
        ans[++acnt] = x * (s - 1);
        // return;
    }
    ll p, v, sv;
    for (; i <= pcnt && (p = pri[i], p * p <= s); ++i)
        for (v = p, sv = 1 + p; sv <= s; v *= p, sv += v)
            if (s % sv == 0)
                dfs(x * v, s / sv, i + 1);
}
int main() {
    static int s, i;
    sieve();
    while (scanf("%d", &s) == 1) {
        acnt = 0;
        dfs(1, s, 1);
        std::sort(ans + 1, ans + acnt + 1);
        printf("%d\n", acnt);
        for (i = 1; i <= acnt; ++i)
            printf("%d%c", ans[i], (i == acnt) ? '\n' : ' ');
    }

    return 0;
}
