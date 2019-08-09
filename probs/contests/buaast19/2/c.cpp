#include <cstdio>
#include <cstring>

const int N = 202;
char s[N];
bool cut[N];
int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%s", s);
        int n = strlen(s);
        int l = 0, r = 0, i;
        for (i = 0; i < n; ++i)
            cut[i] = false;
        while (s[r] == '0')
            ++r;
        while (s[r] == '1')
            ++r;
        if (r >= n) {
            // printf("\nEnd\n");
            printf("%s\n", s);
            continue;
        }
        --r;
        for (i = r + 1; i < n; ) {
            int ll = i;

            while (s[i] == '0')
                ++i;
            while (s[i] == '1')
                ++i;
            
            int rr = i - 1;

           //  printf("\n(%d, %d, %d, %d)\n", l, r, ll, rr);
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
            r = rr;
            if (fail) {
                l = ll;
                cut[ll] = true;
            }
        }
        for (i = 0; i < n; ++i) {
            if (cut[i])
                putchar(' ');
            putchar(s[i]);
        }
        putchar('\n');
    }

    return 0;
}