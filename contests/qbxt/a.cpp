#include <cstdio>
#include <algorithm>

const int MAXM = 100010;
int n, m, s;
int l[MAXM], r[MAXM];
long long k, sum, gain;

struct Record {
    int e;
    long long t;
    bool used;
} qwq[MAXM];
inline bool qaq(const Record &x, const Record &y) {
    return (x.e == y.e) ? (x.t > y.t) : (x.e < y.e);
}
inline bool qaq2(const Record &x, const Record &y) {
    return x.t > y.t;
}

int main() {
    freopen("express.in", "r", stdin);
    freopen("express.out", "w", stdout);
    int i, j, x, c, val;
    scanf("%d%d%d%lld", &n, &m, &s, &k);
    for (i = 1; i <= m; ++i) {
        scanf("%d%lld", &qwq[i].e, &qwq[i].t);
        qwq[i].t -= 2;
        qwq[i].used = false;
    }
    
    if (k > 0) { // k = 0 时必然满足
        std::sort(qwq + 1, qwq + m + 1, qaq);
        l[qwq[1].e] = 1;
        for (i = 2; i <= m; ++i) {
            if (qwq[i].e != qwq[i - 1].e) {
                r[qwq[i - 1].e] = i - 1;
                l[qwq[i].e] = i;
            }
        }
        r[qwq[m].e] = m;
        for (i = 1; i <= n; ++i) {
            if (l[i]) {
                x = r[i] - l[i] + 1;
                sum = 0;
                c = x + 1;
                for (j = 1; j <= x; ++j) {
                    val = qwq[l[i] + j - 1].t;
                    if (val <= 0)
                        break;
                    sum += val;
                    qwq[l[i] + j - 1].used = true;
                    if (sum >= k) {
                        c = j;
                        gain += sum;
                        break;
                    }
                }
                if (c > x) {
                    puts("-23333333\n");
                    return 0;
                } else {
                    s -= c; // 特判 k = 0
                    if (s < 0) {
                        puts("-23333333\n");
                        return 0;
                    }
                }
                // printf("%d at %d, %d needs %d so gained %lld, %d left\n", i, l[i], r[i], c, gain, s);
            }
        }
    } 
    
    std::sort(qwq + 1, qwq + m + 1, qaq2);
    for (i = 1; i <= m; ++i) {
        if (s <= 0 || qwq[i].t <= 0)
            break;
        if (qwq[i].used)
            continue;
        gain += qwq[i].t;
        --s;
    }
    printf("%lld\n", gain);
    return 0;
}
