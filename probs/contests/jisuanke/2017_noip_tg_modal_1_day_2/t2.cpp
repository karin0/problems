#include <cstdio>
const int MAXN = 30020;

int n, a[MAXN]; /* tmp[MAXN];
void sort(int* arr, int l, int r) {
    if (r - l > 1) {
        int mid = (x + y) >> 1;
        sort(arr, l, mid);
        sort(arr, mid, r);
        // .....
    }
}
*/
inline int query(int l, int r) {
    long long cnt = 0;
    for (int i = l; i <= r; ++i) {
        for (int j = i + 1; j <= r; ++j) {
            if (a[i] > a[j])
                ++cnt;
        }
    }
    return cnt;
}

int main() {
    int q, x, y, i;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i)
        scanf("%d", a + i);
    scanf("%d", &q);
    while (q--) {
        scanf("%d%d", &x, &y);
        printf("%d\n", query(x, y));
    }

    return 0;
}
