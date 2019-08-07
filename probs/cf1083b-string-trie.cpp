#include <akari>

IO<1000000, 1000000> io;

cint N = 500002;

char s[N], t[N];
int main() {
    int n, k;
    io >> n >> k >> s >> t;
    ll ans = 0;
    int cnt = 1;
    re (i, 0, n) {
        cnt = (cnt << 1) - (s[i] == 'b') - (t[i] == 'a');
        if (cnt >= k) {
            ans += (ll)(n - i) * k;
            break;
        }
        ans += cnt;
    }
    io << ans daze;
    
    return 0;
}
