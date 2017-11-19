#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

int n = 4, nn = 16, uni, s, t, d[(1 << 16) + 5];
void bfs() {
    static int u, v, i, y;
    static std::queue<int> que;
    que.push(s);
    uni = 1 << nn;
    d[s] = 1;
    while (!que.empty()) {
        u = que.front();
        que.pop();
        if (u == t)
            return;    
        for (i = 0; i < nn; ++i) {
            if ((u >> i) & 1) {
                y = i / n;
                if ((i + 1) / n == y && !((u >> (i + 1)) & 1)) {
                    v = (u & (~(1 << i))) | (1 << (i + 1));
                    // printf("Move1 at %d\n", i);
                    if (!d[v]) {
                        d[v] = d[u] + 1;
                        que.push(v);
                    }
                }
                if (i > 0 && (i - 1) / n == y && !((u >> (i - 1)) & 1)) {
                    v = (u & (~(1 << i))) | (1 << (i - 1));
                    // printf("Move2 at %d\n", i);
                    if (!d[v]) {
                        d[v] = d[u] + 1;
                        que.push(v);
                    }
                }
                if (i + n < nn && !((u >> (i + n)) & 1)) {
                    v = (u & (~(1 << i))) | (1 << (i + n));
                    // printf("Move3 at %d\n", i);
                    if (!d[v]) {
                        d[v] = d[u] + 1;
                        que.push(v);
                    }
                }
                if (i - n >= 0 && !((u >> (i - n)) & 1)) {
                    v = (u & (~(1 << i))) | (1 << (i - n));
                    // printf("Move4 at %d\n", i);
                    if (!d[v]) {
                        d[v] = d[u] + 1;
                        que.push(v);
                    }
                }
            }
        }
    }
}

int main() {
    static int i, j, cnt = 0;
    static char line[7];
    for (i = 0; i < n; ++i) {
        scanf("%s", line);
        for (j = 0; j < n; ++j)
            s |= ((int)(line[j] == '1')) << (cnt++);
    }
    cnt = 0;
    for (i = 0; i < n; ++i) {
        scanf("%s", line);
        for (j = 0; j < n; ++j)
            t |= ((int)(line[j] == '1')) << (cnt++);
    }
    bfs();
    printf("%d\n", d[t] - 1);
    return 0;
}
