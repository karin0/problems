#include <cstdio>
#include <algorithm>
#include <queue>

typedef long long ll;

struct Node {
    ll w;
    int dep;
};
inline bool operator < (const Node &x, const Node &y) {
    return x.w == y.w ? x.dep > y.dep : x.w > y.w;
}

int n, m;
std::priority_queue<Node> pque;

int main() {
    int i, dep;
    ll w, sw, ans = 0;
    Node x, zero = (Node){0, 0};
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i) {
        scanf("%lld", &w);
        pque.push((Node){w, 0});
    }

    while ((n - 1) % (m - 1) != 0)
        pque.push(zero), ++n;
    while (true) {
        sw = 0;
        dep = 0;
        for (i = 1; i <= m; ++i) {
            x = pque.top();
            pque.pop();
            sw += x.w;
            dep = std::max(dep, x.dep); // ***
        }
        ans += sw;
        if (pque.empty()) {
            printf("%lld\n%d\n", ans, dep + 1);
            return 0;
        }
        pque.push((Node){sw, dep + 1});
    }

    return 0;
}
