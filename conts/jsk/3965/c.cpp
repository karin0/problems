#include <cstdio>
#include <cstring>
#include <algorithm>

typedef long long ll;

const int N = 100003, mo = 1000000007;
ll d[N];
int p[N];

inline bool cmp(int i, int j) {
    return d[i] < d[j];
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        d[i] = (ll)x * x + (ll)y * y;
        p[i] = i;
    }
    std::sort(p + 1, p + n + 1, cmp);
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        ans = (ans + d[p[i]] * (i + p[i])) % mo;
    printf("%d\n", ans);
}