#include <cstdio>
#include <cstring>
#include <vector>

const int N = 202;
char s[N];
std::pair<int, int> vec[N];
int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%s", s);
        int cnt = 0;
        int n = strlen(s);
        for (int i = 0; i < n; ) {
            int ll = i;

            while (s[i] == '0')
                ++i;
            while (s[i] == '1')
                ++i;
            
            int rr = i - 1;
            // printf("\n(%d, %d)\n", ll, rr);
            vec[++cnt] = std::make_pair(ll, rr);

            while (cnt >= 2) {
                auto &x = vec[cnt];
                int ll = x.first;
                int rr = x.second;
                auto &y = vec[cnt - 1];
                int l = y.first;
                int r = y.second;
                int l1 = r - l + 1;
                int l2 = rr - ll + 1;
                int len = l1 + l2;

                bool fail = false;
                for (int j = 0; j < len; ++j) {
                    char aj = j < l1 ? s[l + j] : s[ll + j - l1];
                    char bj = j < l2 ? s[ll + j] : s[l + j - l2];
                    if (aj > bj) {
                        fail = true;
                        break;
                    } else if (aj < bj)
                        break;
                }
                if (fail)
                    break;
                else
                    vec[--cnt] = std::make_pair(l, rr);
            }
        }
        for (int j = vec[1].first; j <= vec[1].second; ++j)
            putchar(s[j]);
        for (int i = 2; i <= cnt; ++i) {
            putchar(' ');
            for (int j = vec[i].first; j <= vec[i].second; ++j)
                putchar(s[j]);
        }
        putchar('\n');
    }

    return 0;
}