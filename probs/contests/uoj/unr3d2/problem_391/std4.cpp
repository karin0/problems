#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, int> pli;
const int N = 1e5 + 10;
int n, m, a[N], q[N], head, tail;
ll dp[N];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) {
        dp[i] = 1e18;
        int mx = 0;
        for (int j = 1; j <= min(i, m); ++j) {
            mx = std::max(mx, a[i - j + 1]);
            dp[i] = std::min(dp[i], dp[i - j] + mx);
        }
	}
	printf("%lld\n", dp[n]);
	return 0;
}
