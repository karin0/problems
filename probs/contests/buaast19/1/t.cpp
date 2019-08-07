#include <bits/stdc++.h>

const int N = 2003;
int a[N][N];
std::vector<int> vx[N], vy[N];
std::mt19937 rd(time(NULL));
int main() {
    int n = 2000, k = 85000;
    while (k) {
        int x = rd() % n, y = rd() % n;
        if (a[x][y])
            continue;
        bool fail = false;
        for (const auto &aa : vx[x]) {
            for (const auto &bb : vy[y]) 
                if (a[bb][aa]) {
                    fail = true;
                    break;
                }
            if (fail)
                break;
        }
        if (fail)
            continue;
        --k;
        fprintf(stderr, "%d\n", k);
        vx[x].push_back(y);
        vy[y].push_back(x);
        a[x][y] = 1;
    }
    printf("%d\n", n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            printf("%d", a[i][j]);
        putchar('\n');
    }
}