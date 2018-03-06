#include <cstdio>
#include <algorithm>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))

const int N = 400005, W = 29;
inline bool bit(const int x, const int k) {
    return x >> k & 1;
}
struct Trie *curr;
struct Trie {
    Trie *ch[2];
    Trie(Trie *lc, Trie *rc) {
        ch[0] = lc, ch[1] = rc;
    }
    Trie() {}
    Trie *insert(const int x, const int k = W) const {
        if (k < 0)
            return new (curr++) Trie(ch[0], ch[1]);
        if (bit(x, k))
            return new (curr++) Trie(ch[0], ch[1]->insert(x, k - 1));
        else
            return new (curr++) Trie(ch[0]->insert(x, k - 1), ch[1]);
    }
} pool[N * 32], *nil, *root[N];
inline void init() {
    curr = pool;
    nil = curr++;
    *nil = Trie(nil, nil);
}
int query(const int l, const int r, const int x) {
    static Trie *p, *q;
    static bool v;
    static int k, res;

    p = l ? root[l - 1] : nil;
    q = root[r];
    for (res = 0, k = W; k >= 0; --k) {
        v = !bit(x, k);
        res <<= 1;
        if (p->ch[v] == q->ch[v])
            p = p->ch[!v], q = q->ch[!v];
        else
            p = p->ch[v], q = q->ch[v], res |= 1;
    }
    return res;
}
int main() {
    static int n, i, x, xs[N], ans, ans0;
    init();
    scanf("%d", &n);
    root[0] = nil->insert(0);
    rep (i, 1, n) {
        scanf("%d", &x);
        root[i] = root[i - 1]->insert(xs[i] = xs[i - 1] ^ x);
    }
    // 0 <= l1 < r1 <= l2 < r2 <= n
    re (i, 1, n) { // for each r1
        ans0 = std::max(ans0, query(0, i - 1, xs[i]));
        ans = std::max(ans, ans0 + query(i + 1, n, xs[i]));
    }
    printf("%d\n", ans);

    return 0;
}
