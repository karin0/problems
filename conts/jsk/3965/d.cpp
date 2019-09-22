#include <cstdio>
#include <cstring>
#include <algorithm>

typedef long long ll;

const int N = 100003;

int cnt[103];

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        ++cnt[x];
    }
    ll ans = 0;
    for (int i = 1; i <= 100; ++i) {
        int t = i * i;
        if (t % k == 0)
            ans += ((ll)cnt[i] * (cnt[i] - 1)) >> 1;
        t += i;
        for (int j = i + 1; j <= 100; ++j, t += i)
            if (t % k == 0)
                ans += (ll)cnt[i] * cnt[j];
    }
    printf("%lld\n", ans);
}