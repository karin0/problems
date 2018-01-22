#include <cstdio>
#include <algorithm>

const int N = 50003;
// Informatik verbindet dich und mich.

typedef long long ll;
int mo;
int phi(int x) {
    static int res, i;
    for (res = x, i = 2; i * i <= x; ++i)
        if (x % i == 0) {
            res = res / i * (i - 1);
            do x /= i; while (x % i == 0);
        }
    if (x > 1)
        res = res / x * (x - 1);
    return res;
}
int seq[N], k, pmo[N];
ll pow(ll a, ll x, int m, bool &f) {
    static ll res;
    res = 1, f = false;
    for (; x; x >>= 1, f |= ((a *= a) >= m && x), a %= m)
        if (x & 1)
            f |= (res *= a) >= m, res %= m;
    return res;
}
int c;
int calc(int a, int e) {
    static int i;
    static bool flag;
    a = a < pmo[e] ? a : a % pmo[e] + pmo[e];
    //if (a >= pmo[e])
    //    a = a % pmo[e] + pmo[e];
    for (i = e - 1; i >= 0; --i) {
        a = pow(c, a, pmo[i], flag);
        if (flag)
            a += pmo[i];
    }
    return a % mo;
}
struct Node {
    Node *lc, *rc;
    int l, r, sum, cnt;
    Node (int _l, int _r, Node *_lc, Node *_rc) : lc(_lc), rc(_rc), l(_l), r(_r), cnt(0) {
        if (l == r)
            sum = seq[l] % mo;
        else
            maintain();
    }
    void maintain() {
        if (lc) {
            sum = (lc->sum + rc->sum) % mo;
            cnt = std::min(lc->cnt, rc->cnt);
        }
    }
    void update(int ql, int qr) {
        if (cnt >= k || r < ql || qr < l)
            return;
        if (l == r) {
            sum = calc(seq[l], ++cnt);
            return;
        }
        lc->update(ql, qr);
        rc->update(ql, qr);
        maintain();
    }
    int query(int ql, int qr) {
        if (r < ql || qr < l)
            return 0;
        if (ql <= l && r <= qr)
            return sum;
        return (lc->query(ql, qr) + rc->query(ql, qr)) % mo; // **
    }
} *segt;
Node *build(int l, int r) {
    if (l == r)
        return new Node(l, r, NULL, NULL);
    else {
        int mid = (l + r) >> 1;
        return new Node(l, r, build(l, mid), build(mid + 1, r));
    }
}

int main() {
    static int n, m, i, opt, l, r;
    scanf("%d%d%d%d", &n, &m, &mo, &c);
    for (i = 1; i <= n; ++i)
        scanf("%d", seq + i);
    segt = build(1, n);
    k = 0, pmo[0] = mo;
    while (pmo[k] > 1)
        ++k, pmo[k] = phi(pmo[k - 1]);
    // mo 迭代 k 次后得到 1
    pmo[++k] = 1;
    while (m--) {
        scanf("%d%d%d", &opt, &l, &r);
        if (opt)
            printf("%d\n", segt->query(l, r));
        else
            segt->update(l, r);
    }

    return 0;
}
