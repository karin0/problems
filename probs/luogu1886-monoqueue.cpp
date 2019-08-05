#include <akari>

IO<1000000, 1000000> io;

cint N = 1000002;

int a[N], q[N];
inline void solve(int n, int k, int g) { // for max
    int l = 1, r = 0;
    rep (i, 1, n) {
        while (r - l + 1 && a[q[r]] <= a[i])
            --r;
        while (r - l + 1 && i - q[l] + 1 > k)
            ++l;
        q[++r] = i;
        if (i >= k)
            io << g * a[q[l]] << ' ';
    }
    io daze;
}
int main() {
    int n, k;
    io >> n >> k;
    rep (i, 1, n)
        a[i] = -(int)io;
    solve(n, k, -1);
    rep (i, 1, n)
        a[i] = -a[i];
    solve(n, k, 1);

    return 0;
}
