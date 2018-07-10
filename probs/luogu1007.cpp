// AC
#include <cstdio>
#include <algorithm>
using std::max;
using std::min;

int l, n, pos, mint, maxt;
int main() {
    scanf("%d%d", &l, &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &pos);
        if (pos > l - pos + 1) {
            mint = max(mint, l - pos + 1);
            maxt = max(maxt, pos);
        } else {
            mint = max(mint, pos);
            maxt = max(maxt, l - pos + 1);
        }
    }
    printf("%d %d", mint, maxt);

    return 0;
}
