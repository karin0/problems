#include <cstdio>
#include <algorithm>
#define MAXN 8000010
#define INF 2147483647

struct Akari {
    int len, birth;
};
bool akari_cmp(Akari x, Akari y) {
    return x.len > y.len;
}
struct Queue {
    Akari v[MAXN];
    int head = 1, tail = 0, id;
    void init() {
        // Never poped
        std::sort(v + head, v + tail + 1, akari_cmp);
    }
    void push(int len, int birth) {
        Akari x;
        x.len = len;
        x.birth = birth;
        v[++tail] = x;
    }
    bool empty() {
        return head > tail;
    }
    Akari& front() {
        Akari& res = v[head];
        if (empty()) 
            res.len = (res.birth = -INF); // Len must be also -INF for the coming cmps
        return res;
    }
    void pop() {
        ++head;
    }
} que, quea, queb;

Akari& choose() {
    Akari &x = que.front();
    Akari &y = quea.front();
    Akari &z = queb.front();
    if (x.len >= y.len && x.len >= z.len) que.pop();
    else if (y.len >= x.len && y.len >= z.len) {
        x = y; quea.pop();
    }
    else {
        x = z; queb.pop();
    }
    return x;
}

int n, m, q, u, v, k;
int main() {
    int f, bx;
    long long tmp, ax;
    scanf("%d%d%d%d%d%d", &n, &m, &q, &u, &v, &k);
    if (u * 2 > v)
        u = v - u; // To assume [p*x] <= x - [p*x]
    for (register int i = 1; i <= n; ++i) {
        scanf("%d", &f);
        que.push(f, 0);
    }
    que.init();
    for (register int t = 1; t <= m; ++t) { // t 秒后
        Akari &x = choose();
        //printf("[[At %d, maybe %d ", t, x.len);
        x.len += (t - x.birth) * q;
        tmp = x.len * u;
        ax = tmp / v; // Oops
        bx = x.len - ax;
        //printf("but %d (birth at %d) is made into %d and %d]]\n", x.len, x.birth, ax, bx);
        quea.push((int)ax - q, t);
        queb.push(bx - q, t);
        if (!(t % k)) {
            printf("%d ", x.len);
        }
    }
    printf("\n");
    for (register int rank = 1; ; ++rank) {
        Akari &x = choose();
        if (x.birth == -INF)
            break;
        else if (rank % k)
            continue;
        printf("%d ", x.len + (m - x.birth - 1) * q);
    }
    return 0;
}
