#include <cstdio>
#include <algorithm>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

int main() {
    freopen("katryoshka.in", "r", stdin);
    int t;
    scanf("%d", &t);
    rep (ks, 1, t) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        int t = std::min(a, std::min(b, c));
        a -= t;
        // b -= t;
        c -= t;
        int u = std::min(a >> 1, c);
        printf("Case %d: %d\n", ks, t + u);
    }

    return 0;
}
