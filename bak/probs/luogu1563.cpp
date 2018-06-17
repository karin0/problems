#include <cstdio>

const int MAXN = 100005;
int n, face[MAXN];
char job[MAXN][13];

int main() {
    static int m, i, a, d, pos;
    scanf("%d%d", &n, &m);
    for (i = 0; i < n; ++i)
        scanf("%d%s", face + i, job[i]);
    for (i = 0; i < m; ++i) {
        scanf("%d%d", &a, &d);
        if (a == 0)
            d = -d;
        if (face[pos] == 1)
            d = -d;
        pos = ((pos + d) % n + n) % n;
    }
    printf("%s\n", job[pos]);

    return 0;
}
