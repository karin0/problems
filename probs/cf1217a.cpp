#include <cstdio>
#include <algorithm>

int main() {
    int T;
    std::scanf("%d", &T);
    while (T--) {
        int s, i, e;
        std::scanf("%d%d%d", &s, &i, &e);
        std::printf("%d\n", std::max(0, e - std::max(0, (i + e - s + 2) >> 1) + 1));
    }
}