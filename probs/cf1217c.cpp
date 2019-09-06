#include <akari>

IO<1000000, 1000000> io;

cint N = 200003;
char s[N];
int pre[N];
int main() {
    int T;
    io >> T;
    while (T--) {
        int n = io.gs(s + 1) - (s + 1), pr = 0, ans = 0, x, len;
        rep (i, 1, n) {
            pre[i] = pr;
            if (x = s[i] == '1')
                ++ans, pr = i;
            for (int j = pre[i]; j && (len = i - j + 1) <= 18; j = pre[j]) {
                x |= 1 << (i - j);
                if (x >= len && x <= i - pre[j])
                    ++ans;
            }
        }
        io << ans daze;
    }
}
