#include <cstdio>
#include <algorithm>
#include <set>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))

const int N = 50005, W = 29;
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
    p = root[l - 1];
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
int a[N];
inline bool cmp(const int lhs, const int rhs) {
    return a[lhs] > a[rhs];
}
int main() {
    static int n, i, x, ans, qaq[N];
    static std::set<int> s;
    static std::set<int>::iterator l, r;
    init();
    scanf("%d", &n);
    root[0] = nil;
    rep (i, 1, n) {
        scanf("%d", &a[i]);
        root[i] = root[i - 1]->insert(a[i]);
        qaq[i] = i;
    }
    std::sort(qaq + 1, qaq + n + 1, cmp);
    s.insert(0);
    s.insert(n + 1);
    // 对于前缀, 后缀的信息, 有时控制结点插入顺序可以完成可持久化的工作. 这个顺序有可能是位置上的, 也可能是值上的.
    rep (i, 1, n) {
        x = qaq[i];
        s.insert(x);
        l = r = s.find(x);
        if (*--l > 0)
            --l;
        if (*++r <= n)
            ++r;
        ans = std::max(ans, query(*l + 1, *r - 1, a[x]));
    }
    printf("%d\n", ans);

    return 0;
}
