#include <cstdio>
#include <algorithm>
#define MAXN 9500010
#define INF (1L<<60)

bool cmp(long long x, long long y) {
    return x > y;
}
struct Queue {
    long long v[MAXN];
    int head, tail, id;
    Queue() : head(1), tail(0) {}
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
    long long front() {
        if (empty()) 
            return -INF;    
        return v[head];
    }
    void pop() {
        ++head;
    }
} que, quea, queb;

long long choose() {
    long long x = que.front();
    long long y = quea.front();
    long long z = queb.front();
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
    long long f, ax, bx;
    bool ioflag;
    scanf("%d%d%d%d%d%d", &n, &m, &q, &u, &v, &k);
    for (register int i = 1; i <= n; ++i) {
        scanf("%lld", &f);
        que.push(f);
    }
    que.init();
    ioflag = false;
    for (register int t = 1; t <= m; ++t) { // t 秒后
        long long x = choose();
        //printf("[[At %d, maybe %d ", t, x.len);
        x += (t - 1) * q;
        ax = (x * u) / v; // Oops
        bx = x - ax;
        //printf("but %d (birth at %d) is made into %d and %d]]\n", x.len, x.birth, ax, bx);
        quea.push(ax - t * q);
        queb.push(bx - t * q);
        if (!(t % k)) {
            if (ioflag)
                printf(" ");
            printf("%lld", x);
            ioflag = true;
        }
    }
    printf("\n");
    ioflag = false;
    for (register int rank = 1; ; ++rank) {
        long long x = choose();
        if (x == -INF)
            break;
        else if (rank % k)
            continue;
        if (ioflag)
            printf(" ");
        printf("%lld", x + m * q);
        ioflag = true;
    }
    // printf("\n");
    return 0;
}
