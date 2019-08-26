#include <cstdio>
#include <cctype>
#include <algorithm>

typedef long long ll;
const int MAXS = 5000015, mo = 998244353, ba = 131;
char s[MAXS];
int k, ha[MAXS], ans = 0, l[MAXS], pba = 1, cnt = 1, n, h;
int main() {
    static int i;
    scanf("%s%d", s + 1, &k);
    for (i = 1; s[i]; ++i)
        ha[i] = ((ll)ha[i - 1] * ba + (s[i] - 'A' + 1)) % mo;
    n = i - 1;
    h = n - k + 1;
    for (i = 1; i <= k; ++i)
        pba = (ll)pba * ba % mo;
    for (i = 1; i <= h; ++i)
        l[i] = (((ll)ha[i + k - 1] - (ll)ha[i - 1] * pba) % mo + mo) % mo; // printf("l[%d] == %d\n", i, l[i]);
    std::sort(l + 1, l + n - k + 2);
    for (i = 2; i <= h; ++i) {
        // printf("l[%d] == %d\n", i, l[i]);
        if (l[i] == l[i - 1])
            ++cnt;
        else
            ans = std::max(ans, cnt), cnt = 1;
    }
    printf("%d\n", std::max(ans, cnt));
    return 0;
}
