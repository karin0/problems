#include <cstdio>

unsigned char a[1000001];
int i, n, t, p;
bool same;
unsigned int x;
int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (i = 0; i < n; ++i) {
            scanf("%u", &x);
            a[i] = x % 244;
        }
        same = true;
        for (i = 0; i < n; ++i) {
            scanf("%u", &x);
            if (same && a[i] != x % 244)
                same = false, p = i + 1;
        }
        if (same)
            puts("0");
        else
            printf("1 %d\n", p);
    }

    return 0;
}
