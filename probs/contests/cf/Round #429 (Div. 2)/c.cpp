#include <cstdio>
#include <algorithm>

const int MAXN = 200010;

struct Data {
    int i, v;
} a[MAXN], b[MAXN];
bool qaq(Data &a, Data &b) {
    return a.v < b.v;
}

int n, ans[MAXN];
int main() {
    scanf("%d", &n);
    int i;
    for (i = 1; i <= n; ++i) {
        scanf("%d", &a[i].v);
        a[i].i = i;
        a[i].v = -a[i].v;
    }
    for (i = 1; i <= n; ++i)
        scanf("%d", &b[i].v), b[i].i = i;
    std::sort(a + 1, a + n + 1, qaq);
    std::sort(b + 1, b + n + 1, qaq);
    for (i = 1; i <= n; ++i)
        ans[b[i].i] = -a[i].v;
    for (i = 1; i <= n; ++i)
        printf("%d ", ans[i]);
    // printf("\n");
    return 0;
}
