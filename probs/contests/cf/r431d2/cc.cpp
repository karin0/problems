#include <cstdio>
#include <algorithm>

const int MAXX = 500;

int a[MAXX];

int main() {
    int i, k, pos;
    scanf("%d", &k);
    if (k == 0) {
        printf("a");
        return 0;
    }
    int ch = 0;
    while (k) {
        printf("%c", ch + 97);
        for (int i = 1; i <= k; ++i)
            if (k >= i)
                k -= i, printf("%c", ch + 97);
            else
                break;
        ++ch;
    }
    return 0;
}
