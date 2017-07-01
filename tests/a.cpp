#include<cstdio>
#include<cstring>
#include<algorithm>
//using namespace std;
const int N = 100003;
int t1[N], t2[N], c[N];
void st(int *x, int *y, int *sa, int n, int m) {
    for (int i = 0; i <= m; ++i) c[i] = 0;
    for (int i = 0; i < n; ++i) ++c[x[y[i]]];
    for (int i = 1; i <= m; ++i) c[i] += c[i - 1];
    for (int i = n - 1; i >= 0; --i) sa[--c[x[y[i]]]] = y[i];
}
void mkhz(int *r, int *sa, int n, int m) {
    int *x, *y, *t, i, j, p;
    x = t1; y = t2;
    for (i = 0; i < n; ++i) x[i] = r[i], y[i] = i;
    st(x, y, sa, n, m);
    for (p = 1, j = 1; j < n && p < n; j <<= 1, m = p - 1) {
        for (p = 0, i = n - j; i < n; ++i) y[p++] = i;
        for (i = 0; i < n; ++i) if (sa[i] >= j) y[p++] = sa[i] - j;
        st(x, y, sa, n, m);
        for (t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; ++i)
            x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + j] == y[sa[i] + j] ? p - 1 : p++;
    }
}
void mkh(int *r, int *sa, int *rank, int *h, int n) {
    h[1] = 0; int k = 0, j;
    for (int i = 1; i < n; ++i) rank[sa[i]] = i;
    for (int i = 1; i < n; h[rank[i++]] = k)
        for (k ? --k : k = 0, j = sa[rank[i] - 1]; r[j + k] == r[i + k]; ++k);
}
char s[N];
int r[N], sa[N], h[N], rank[N];
int main() {
    scanf("%s", s + 1);
    int len = strlen(s + 1);
    for (int i = 1; i <= len; ++i) r[i] = s[i] - 'a' + 1;
    mkhz(r, sa, len + 1, 26);
    for (int i = 1; i <= len; ++i) printf("%d ", sa[i]);
    puts("");
    mkh(r, sa, rank, h, len + 1);
    for (int i = 2; i <= len; ++i) printf("%d ", h[i]);
    puts("");
    return 0;
}
