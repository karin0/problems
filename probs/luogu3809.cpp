// 后缀数组模板
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 5000010

char s[MAXN], n;
int key1[MAXN], key2[MAXN], tmp[MAXN], cnt[MAXN];
int rank[MAXN], sa[MAXN];
void generate_sa() {
    n = strlen(s) + 1;
    s[n] = 0; // least
    int m = -1;
    for (int i = 0; i < n; ++i) {
        m = std::max(m, (int)s[i]);
        ++cnt[s[i]];
    };
    for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; ++i) rank[i] = cnt[s[i]] - 1; // Rank starts from 0
    
    bool unique;
    for (int l = 1; l < n; l <<= 1) { // ???
        for (int i = 0; i < n; ++i) {
            key1[i] = rank[i];
            key2[i] = i + l < n ? key1[i + l] : 0;
        }
        std::fill(cnt, cnt + n, 0);
        for (int i = 0; i < n; ++i) ++cnt[key2[i]];
        for (int i = 0; i < n; ++i) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; --i) tmp[--cnt[key2[i]]] = i;
        std::fill(cnt, cnt + n, 0);
        for (int i = 0; i < n; ++i) ++cnt[key1[i]];
        for (int i = 0; i < n; ++i) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; --i) sa[--cnt[key1[tmp[i]]]] = tmp[i];

        unique = true;
        rank[sa[0]] = 0;
        for (int i = 1; i < n; ++i) {
            rank[sa[i]] = rank[sa[i - 1]];
            if (key1[sa[i]] == key1[sa[i - 1]] && key2[sa[i]] == key2[sa[i - 1]]) unique = false;
            else ++rank[sa[i]];
        }
        if (unique) break;
    }
}

int main() {
    scanf("%s", s);
    generate_sa();
    for (int i = 1; i < n; ++i) { // the 0th smallest is the last 0 char
        printf("%d ", sa[i] + 1);
    }
}
