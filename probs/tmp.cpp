#include <cstdio>
#include <cstring>
#include <stack>
const int MAXN = 500005;
namespace SuffixArray {
    int rank[MAXN], sa[MAXN], height[MAXN], n;
    char str[MAXN];
    void buildSA(int m) {
        static int fir[MAXN], sec[MAXN], temp[MAXN], cnt[MAXN], i;
        n = strlen(str) + 1;
        str[n - 1] = 0;
        memset(cnt, 0, sizeof cnt);
        for (i = 0; i < n; i++) cnt[(int) str[i]]++;
        for (i = 1; i < m; i++) cnt[i] += cnt[i - 1];
        for (i = 0; i < n; i++) rank[i] = cnt[(int) str[i]] - 1;
        for (i = 0; i <= n; ++i) {
            printf("%d %c %d\n", i, str[i], rank[i]);
        }
        for (int l = 1; l < n; l <<= 1) {
            for (int i = 0; i < n; i++)
                fir[i] = rank[i], sec[i] = i + l < n ? rank[i + l] : 0;
            memset(cnt, 0, sizeof cnt);
            for (i = 0; i < n; i++) cnt[sec[i]]++;
            for (i = 1; i < n; i++) cnt[i] += cnt[i - 1];
            for (i = n - 1; ~i; i--) temp[--cnt[sec[i]]] = i;
            memset(cnt, 0, sizeof cnt);
            for (i = 0; i < n; i++) cnt[fir[i]]++;
            for (i = 1; i < n; i++) cnt[i] += cnt[i - 1];
            for (i = n - 1; ~i; i--) sa[--cnt[fir[temp[i]]]] = temp[i];
            bool unique = true;
            rank[sa[0]] = 0;
            for (i = 1; i < n; i++) {
                rank[sa[i]] = rank[sa[i - 1]];
                if (fir[sa[i]] == fir[sa[i - 1]] && sec[sa[i]] == sec[sa[i - 1]]) 
                    unique = false;
                else rank[sa[i]]++;
            }
            if (unique) break;
        }
    }
    void getHeight() {
        int k = 0;
        for (int i = 0; i < n - 1; i++) {
            k ? k-- : 0;
            int j = sa[rank[i] - 1];
            while (str[i + k] == str[j + k]) k++;
            height[rank[i]] = k;
        }
    }
}
int main() {
    char *str = SuffixArray::str;
    scanf("%s", str);
    int n = strlen(str);
    SuffixArray::buildSA(128);
    SuffixArray::getHeight();
    int *height = SuffixArray::height + 1, *sa = SuffixArray::sa;
    for (int i = 1; i <= n; i++) printf("%d%c", sa[i], i == n ? '\n' : ' ');
    for (int i = 1; i < n; i++) printf("%d%c", height[i], i == n - 1 ? '\n' : ' ');
    return 0;
}
