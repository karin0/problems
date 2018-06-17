#include <cstdio>
#include <cmath>

int p;
int main() {
    int q, sq, i, ans;
    scanf("%d", &q);
    while (q--) {
        scanf("%d", &p);
        p -= 1;
        ans = 0;
        sq = round(sqrt(p));
        for (i = 1; i < sq; ++i)
            if (!(p % i))
                ans += 2;
        if (!(p % sq))
            ans += 1;
        printf("%d\n", ans);
    }
    return 0;
}
