// Make every int to long long and AC finally.
#include <cstdio>
#include <algorithm>
#define MAXN 9500010
#define INF 2147483647

bool cmp(int x, int y) {
    return x > y;
}
struct Queue {
    int v[MAXN];
    int head = 1, tail = 0, id;
    void init() {
        // Never poped
        std::sort(v + head, v + tail + 1, cmp);
    }
    void push(int x) {
        v[++tail] = x;
    }
    bool empty() {
        return head > tail;
    }
    int front() {
        if (empty()) 
            return -INF;    
        return v[head];
    }
    void pop() {
        ++head;
    }
} que, quea, queb;

int choose() {
    int x = que.front();
    int y = quea.front();
    int z = queb.front();
    if (x >= y && x >= z)
        que.pop();
    else if (y >= x && y >= z) 
        x = y, quea.pop();
    else {
        x = z, queb.pop();
    }
    return x;
}

int n, m, q, u, v, k;
int main() {
    int f;
    long long tmp, ax, bx;
    scanf("%d%d%d%d%d%d", &n, &m, &q, &u, &v, &k);
    for (register int i = 1; i <= n; ++i) {
        scanf("%d", &f);
        que.push(f);
    }
    que.init();
    for (register int t = 1; t <= m; ++t) { // t 秒后
        int x = choose();
        //printf("[[At %d, maybe %d ", t, x.len);
        x += (t - 1) * q;
        tmp = x * u;
        ax = tmp / v; // Oops
        bx = x - ax;
        //printf("but %d (birth at %d) is made into %d and %d]]\n", x.len, x.birth, ax, bx);
        quea.push(ax - t * q);
        queb.push(bx - t * q);
        if (!(t % k)) {
            printf("%d ", x);
        }
    }
    printf("\n");
    for (register int rank = 1; ; ++rank) {
        int x = choose();
        if (x == -INF)
            break;
        else if (rank % k)
            continue;
        printf("%d ", x + m * q);
    }
    return 0;
}
