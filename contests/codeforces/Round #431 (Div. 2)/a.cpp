#include <cstdio>

const int MAXN = 2e5 + 10;

int n;

int main() {
    int s, t, i;
    scanf("%d", &n);
    if (n & 1) {
        scanf("%d", &s);
        for (i = 1; i < n; ++i)
            scanf("%d", &t);
        if (n == 1)
            t = s;
        printf(((s & 1) && (t & 1)) ? "Yes\n" : "No\n");
    } else {
        for (i = 0; i < n; ++i)
            scanf("%d", &t);
        printf("No\n");
    }

    return 0;
}
