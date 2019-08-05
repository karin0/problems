#include <akari>

IO<1000000, 10> io;

cint N = 50002;

struct S {
    int x, id;
    bool operator < (const S &rhs) const {
        return x < rhs.x;
    }
} a[N];
int ha[N], cnt[N];
int main() {
    int n = io;
    rep (i, 1, n) {
        io >> a[i].x;;
        a[i].id = ha[i] = io;
    }
    std::sort(ha + 1, ha + n + 1);
    int *end = std::unique(ha + 1, ha + n + 1), m = end - ha - 1;
    rep (i, 1, n)
        a[i].id = std::lower_bound(ha + 1, end, a[i].id) - ha;
    std::sort(a + 1, a + n + 1);
    
    int j = 1, ans = INT_MAX, tot = 0;
    rep (i, 1, n) {
        int *p = &cnt[a[i].id];
        if (++*p == 1)
            ++tot;
        while (j < i && *(p = &cnt[a[j].id]) > 1) {
            ++j;
            --*p;
        }
        if (tot == m)
            ans = std::min(ans, a[i].x - a[j].x);
    }
    io << ans daze;
    
    return 0;
}
