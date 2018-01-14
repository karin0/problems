#include <cstdio>
#include <cstring>
#include <algorithm>

typedef unsigned long long ull;
const int MAXN = 100009;
const int base = 27; // mo = 2147483647;
int n;
char s[MAXN];
ull bp[MAXN];
struct Node *root;
struct Node {
    Node *fa, *ch[2];
    int c, size;
    ull ha;
    Node(Node *_fa, int _c) : fa(_fa), c(_c), ha(_c), size(1) {}
    void link(Node *o, Node *p, int r) {
        if (o)
            o->fa = p;
        if (p)
            p->ch[r] = o;
    }
    int get_size(Node *o) {
        return o ? o->size : 0;
    }
    ull get_hash(Node *o) {
        return o ? o->ha : 0;
    }
    int rel() {
        return fa ? (this == fa->ch[1]) : 0;
    }
    void maintain() {
        int s0 = get_size(ch[0]), s1 = get_size(ch[1]);
        // printf("%c, %d, %d\n", c + 'a' - 1, s0, s1);
        size = 1 + s0 + s1;
        ha = get_hash(ch[1]) + (ull)c * bp[s1] + get_hash(ch[0]) * bp[s1 + 1]; // ***
    }
    void rotate() {
        Node *f = fa;
        int r = rel();
        link(this, f->fa, f->rel());
        link(ch[r ^ 1], f, r);

        link(f, this, r ^ 1);
        f->maintain();
        maintain();
        if (fa == NULL)
            root = this;
        else
            fa->maintain();
    }
    void splay(Node *dest = NULL) { // 目标节点的父节点
        while (fa != dest) {
            if (fa->fa == dest)
                rotate();
            else if (fa->rel() == rel())
                fa->rotate(), rotate();
            else
                rotate(), rotate();
        }
    }
    int rank() {
        return get_size(ch[0]);
    }
};
Node *select(int k) {
    Node *o = root;
    int ork;
    while (true) {
        ork = o->rank();
        if (k < ork)
            o = o->ch[0];
        else if (k >= ork + 1) {
            k -= ork + 1;
            o = o->ch[1];
        } else
            break;
    }
    o->splay();
    return o;
}
Node *build(int l, int r, Node *fa) {
    if (l > r)
        return NULL;
    int mid = (l + r) >> 1;
    Node *o = new Node(fa, s[mid] - 'a' + 1);
    if (l < r) {
        o->ch[0] = build(l, mid - 1, o); // **
        o->ch[1] = build(mid + 1, r, o);
    }
    o->maintain();
    // printf("%d ~ %d is %c, ha = %d\n", l, r, o->c - 1 + 'a', o->ha);
    return o;
}
void init() {
    root = build(0, n + 1, NULL);
}
ull get_hash(int l, int r) {
    static Node *p, *q;
    q = select(r + 1);
    p = select(l - 1);
    p->splay();
    q->splay(p);
    // q->ch[0]->maintain();
    // printf("Get %d\n", q->ch[0]->ha);
    return q->ch[0]->ha;
}
inline bool check(char c) {
    return c >= 'a' && c <= 'z';
}

int main() {
    static int i, m, x, y, lb, rb, mid, c;
    static char opt[3], *ptr, ch;
    static Node *p, *q, *o;
    // freopen("bzoj_1014.in", "r", stdin);
    // freopen("bzoj_1014.out", "w", stdout);
    ptr = s + 1, ch = 0;
    while (!check(ch))
        ch = getchar();
    while (check(ch))
        *ptr = ch, ++ptr, ch = getchar();
    n = ptr - s - 1;
    scanf("%d", &m);
    s[0] = s[n + 1] = 'a';
    bp[0] = 1;
    for (i = 1; i <= n + 2; ++i)
        bp[i] = bp[i - 1] * base;
    init();
    while (m--) {
        scanf("%s%d", opt, &x);
        if (opt[0] == 'Q') {
            scanf("%d", &y);
            lb = 0, rb = n - std::max(x, y) + 2; // n could have been changed!
            while (rb - lb > 1) {
                mid = (lb + rb) >> 1;
                // printf("Trying %d\n", mid);
                if (get_hash(x, x + mid - 1) == get_hash(y, y + mid - 1))
                    lb = mid;
                else
                    rb = mid;
            }
            if (std::max(x, y) + lb - 1 > n)
                --lb;
            printf("%d\n", lb);
        } else if (opt[0] == 'I') {
            scanf("%s", opt);
            c = opt[0] - 'a' + 1;
            ++n; // **
            bp[n + 2] = bp[n + 1] * base;
            p = select(x);
            q = select(x + 1);
            p->splay();
            q->splay(p);
            q->ch[0] = new Node(q, c);
            // q->maintain();
            // p->maintain();
        } else {
            scanf("%s", opt);
            c = opt[0] - 'a' + 1;
            o = select(x);
            o->c = c;
            // o->maintain();
        }
    }
    return 0;
}
