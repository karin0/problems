#include <cstdio>

const int N = 202;
int main() {
    static int t, x, i, j, n;
    static bool ci[N], cj[N];
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (i = 1; i <= n; ++i)
            for (j = 1; j <= n; ++j)
                if (scanf("%d", &x), x)
                    ci[i] = cj[j] = true;
        bool ok = true;
        for (i = 1; i <= n; ++i)
            if (!(ci[i] && cj[i])) {
                ok = false;
                break;
            }
        puts(ok ? "Yes" : "No");
        if (t)
            for (i = 1; i <= n; ++i)
                ci[i] = cj[i] = false;
    }

    return 0;
}
