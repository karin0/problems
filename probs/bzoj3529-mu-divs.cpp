#include <cstdio>
#include <algorithm>

const int N = 100003, Q = 20003;
bool np[N];
int pri[N], mu[N], z[N], pcnt, mn = 1;
struct Pair {
    int v, i;
    bool operator < (const Pair &rhs) const {
        return v < rhs.v;
    }
} sig[N];
typedef long long ll;
void init(const int n) {
    static int i, j;
    static ll v;
    np[0] = np[1] = true;
    mu[1] = 1;
    sig[1].v = sig[1].i = 1;
    for (i = 2; i <= n; ++i) {
        sig[i].i = i;
        if (!np[i]) {
            pri[pcnt++] = i;
            mu[i] = -1;
            z[i] = i;
            sig[i].v = i + 1;
        }
        for (j = 0; j < pcnt && (v = (ll)i * pri[j]) <= n; ++j) {
            np[v] = true;
            if (i % pri[j] == 0) {
                mu[v] = 0;
                z[v] = z[i] * pri[j];
                sig[v].v = sig[i].v + z[v] * sig[v / z[v]].v;
                break;
            }
            mu[v] = -mu[i];
            z[v] = pri[j];
            sig[v].v = (pri[j] + 1) * sig[i].v;
        }
    }
    std::sort(sig + 1, sig + n + 1);
}
struct BIT {
    int c[N];
    inline static int lowbit(const int x) {
        return x & -x;
    }
    int query(int o) const {
        static int res;
        for (res = 0; o >= 1; o -= lowbit(o))
            res += c[o];
        return res;
    }
    void add(int o, const int x) {
        for (; o <= mn; o += lowbit(o))
            c[o] += x;
    }
} bit;
void update(const int x, const int v) {
    static int i, j;
    for (i = x, j = 1; i <= mn; i += x, ++j)
        if (mu[j])
            bit.add(i, v * mu[j]);
}
int cur = 1;
struct Query {
    int n, m, a, *ans;
    bool operator < (const Query &rhs) const {
        return a < rhs.a;
    }
    void calc() {
        static int i, r, x, y;
        for (; cur <= mn && sig[cur].v <= a; ++cur)
            update(sig[cur].i, sig[cur].v);
        for (i = 1; i <= n; i = r + 1) {
            x = n / i, y = m / i;
            r = std::min(n / x, m / y);
            *ans += (bit.query(r) - bit.query(i - 1)) * x * y;
        }
    }
} qwq[Q];
int main() {
    static int q, i, n, m, ans[Q];
    scanf("%d", &q);
    for (i = 0; i < q; ++i) {
        Query &qq = qwq[i];
        scanf("%d%d%d", &n, &m, &qq.a);
        if (n > m)
            std::swap(n, m);
        mn = std::max(mn, n);
        qq.n = n, qq.m = m;
        qq.ans = &ans[i];
    }
    init(mn);
    std::sort(qwq, qwq + q);
    for (i = 0; i < q; ++i)
        qwq[i].calc();
    for (i = 0; i < q; ++i)
        printf("%d\n", ans[i] & 0x7fffffff);
    return 0;
}
