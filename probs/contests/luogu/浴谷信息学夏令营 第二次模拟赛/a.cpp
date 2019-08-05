#include <cstdio>
#include <algorithm>
const int MAXN = 2007;

struct City {
    int imp, no, same;
} citys[MAXN];
bool cmp(City a, City b) {
    return a.imp > b.imp;
}

int n, ans[MAXN];

int main() {
    scanf("%d", &n);
    register int i;
    for (i = 1; i <= n; ++i) {
        scanf("%d", &citys[i].imp);
        citys[i].no = i;
        citys[i].same = 1;
    }
    std::sort(citys + 1, citys + n + 1, cmp);
    ans[citys[1].no] = 1;
    for (i = 2; i <= n; ++i) 
        if (citys[i].imp == citys[i - 1].imp) {
            citys[i].same = citys[i - 1].same + 1;
            ans[citys[i].no] = ans[citys[i - 1].no];
        } else
            ans[citys[i].no] = ans[citys[i - 1].no] + citys[i - 1].same;
    for (i = 1; i <= n; ++i)
        printf("%d ", ans[i]);

    return 0;
}
