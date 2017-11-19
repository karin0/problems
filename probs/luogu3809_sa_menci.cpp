// 后缀数组模板
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 5000010

char s[MAXN], n;
int rk[MAXN], sa[MAXN];
inline void suffixArray()
{
    static int set[MAXN + 1], a[MAXN + 1];
    std::copy(s + 1, s + n + 1, set + 1);
    std::sort(set + 1, set + n + 1);
    int *end = std::unique(set + 1, set + n + 1);
    for (int i = 1; i <= n; i++) a[i] = std::lower_bound(set + 1, end, s[i]) - set;

    static int fir[MAXN + 1], sec[MAXN + 1], tmp[MAXN + 1], buc[MAXN + 1];
    for (int i = 1; i <= n; i++) buc[a[i]]++;
    for (int i = 1; i <= n; i++) buc[i] += buc[i - 1];
    for (int i = 1; i <= n; i++) rk[i] = buc[a[i] - 1] + 1;

    for (int t = 1; t <= n; t *= 2)
    {
        for (int i = 1; i <= n; i++) fir[i] = rk[i];
        for (int i = 1; i <= n; i++) sec[i] = i + t > n ? 0 : rk[i + t];

        std::fill(buc, buc + n + 1, 0);
        for (int i = 1; i <= n; i++) buc[sec[i]]++;
        for (int i = 1; i <= n; i++) buc[i] += buc[i - 1];
        for (int i = 1; i <= n; i++) tmp[n - --buc[sec[i]]] = i;

        std::fill(buc, buc + n + 1, 0);
        for (int i = 1; i <= n; i++) buc[fir[i]]++;
        for (int i = 1; i <= n; i++) buc[i] += buc[i - 1];
        for (int j = 1, i; j <= n; j++) i = tmp[j], sa[buc[fir[i]]--] = i;

        bool unique = true;
        for (int j = 1, i, last = 0; j <= n; j++)
        {
            i = sa[j];
            if (!last) rk[i] = 1;
            else if (fir[i] == fir[last] && sec[i] == sec[last]) rk[i] = rk[last], unique = false;
            else rk[i] = rk[last] + 1;

            last = i;
        }

        if (unique) break;
    }

}

int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    suffixArray();
    for (int i = 1; i <= n; ++i) { // the 0th smallest is the last 0 char
        printf("%d ", sa[i]);
    }
}
