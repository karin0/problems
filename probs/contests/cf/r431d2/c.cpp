#include <cstdio>
#include <algorithm>

const int MAXX = 500;

int a[MAXX];

int main() {
    int i, k, pos;
    scanf("%d", &k);
    if (!k) {
        printf("a\n");
        return 0;
    }
    for (i = 1; i <= MAXX; ++i) {
        a[i] = (i * (i - 1)) >> 1;
        if (a[i] > k)
            break;
    }
    i -= 1;
    char ch = 'a';
    while (k) {
        pos = std::upper_bound(a + 1, a + i + 1, k) - 1 - a; // 第一个小于等于 ｋ 的位置
        k -= a[pos];
        for (i = 1; i <= pos; ++i)
            putchar(ch);
        ++ch;
    }
    putchar('\n');

    return 0;
}
