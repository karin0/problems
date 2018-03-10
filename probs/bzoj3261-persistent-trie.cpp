#include <cstdio>
#include <new>
 
const int N = 600005, W = 23;
inline bool bit(const int x, const int k) {
    return (x >> k) & 1;
}
struct Trie *curr, *nil;
struct Trie {
    Trie *ch[2];
    Trie(Trie *lc, Trie *rc) {
        ch[0] = lc, ch[1] = rc;
    }
    Trie() {}
 
    Trie *insert(const int x, const int k = W) {
        if (k < 0)
            return new (curr++) Trie(nil, nil);
        if (bit(x, k))
            return new (curr++) Trie(ch[0], ch[1]->insert(x, k - 1));
        else
            return new (curr++) Trie(ch[0]->insert(x, k - 1), ch[1]);
    }
    /*
    bool find(const int x, const int k = W) {
        printf("finding %d, %d ..\n", x, k);
        if (k < 0)
            return this != nil;
        return this != nil && ch[bit(x, k)]->find(x, k - 1);
    }*/
} pool[N * W], *root[N];
inline void init() {
    curr = pool;
    nil = curr++;
    *nil = Trie(nil, nil);
}
int query(const int l, const int r, const int x) {
    static Trie *p, *q;
    static int res, k;
    static bool v;
    p = l ? root[l - 1] : nil;
    q = root[r];
    for (res = 0, k = W; k >= 0; --k) {
        v = !bit(x, k);
        if (p->ch[v] == q->ch[v])
            p = p->ch[!v], q = q->ch[!v], res = res << 1;
        else
            p = p->ch[v], q = q->ch[v], res = (res << 1) | 1;
    }
    return res;
}
 
int main() {
    static int n, m, i, l, r, x, xs;
    static char opt[4];
    init();
    scanf("%d%d", &n, &m);
    root[0] = nil->insert(0);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &x);
        root[i] = root[i - 1]->insert(xs ^= x);
    }
    while (m--) {
        scanf("%s", opt);
        if (opt[0] == 'A') {
            scanf("%d", &x);
            ++n;
            root[n] = root[n - 1]->insert(xs ^= x);
        } else {
            scanf("%d%d%d", &l, &r, &x);
            printf("%d\n", query(l - 1, r - 1, xs ^ x));
        }
    }
 
    return 0;
}
