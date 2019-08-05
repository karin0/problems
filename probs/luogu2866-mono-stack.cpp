#include <akari>

IO<1000000, 20> io;

cint N = 80002;

int s[N];
int main() {
    int n = io, siz = 0;
    ll ans = 0;
    rep (i, 1, n) {
        int h = io;
        while (siz && h >= s[siz])
            --siz;
        ans += siz;
        s[++siz] = h;
    }
    io << ans daze;

    return 0;
}
