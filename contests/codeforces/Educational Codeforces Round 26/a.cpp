#include <cstdio>
#include <algorithm>

int n, vol_cur, vol;
char text[300];
int main() {
    scanf("%d", &n);
    while ((text[0] < 'a' || text[0] > 'z') && (text[0] < 'A' || text[0] > 'Z'))
        text[0] = getchar();
    for (int i = 1; i < n; ++i)
        text[i] = getchar(); // 魔法读入
    for (char *c = &text[0]; *c; ++c) {
        if (*c == ' ') {
            vol = std::max(vol, vol_cur);
            vol_cur = 0;
        } else if (*c >= 'A' && *c <= 'Z')
            ++vol_cur;
    }
    vol = std::max(vol, vol_cur);
    printf("%d\n", vol);
    return 0;
}
