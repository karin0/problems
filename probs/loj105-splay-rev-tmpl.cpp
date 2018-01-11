#include <cstdio>
#include <climits>

struct Node *root;
struct Node {
    Node *fa, *ch[2];
    int x, size, cnt;
    bool rev, bound;

    Node(Node *_fa, int _x, bool _bound) : fa(_fa), x(_x), size(1), rev(false), bound(_bound) {}
    int rel() {
        return this == fa->ch[1];
    }
    void maintain() {
        size = cnt;
        if (ch[0])
            size += ch[0]->size;
        if (ch[1])
            size += ch[1]->size;
    }
    void push_down() {
        if (rev) {
            std::swap(ch[0], ch[1]);
            if (ch[0])
                ch[0]->rev ^= 1;
            if (ch[1])
                ch[1]->rev ^= 1;
            rev = false;
        }
    }
    void rotate() {
        fa->push_down();
        push_down();
        Node *of = fa;
        int r = rel();
        fa = of->fa;
        if (fa)
            fa->ch[of->rel()] = this;
        if (ch[r ^ 1])
            ch[r ^ 1]->fa = of;
        of->ch[r] = ch[r ^ 1];
        of->fa = this;
        ch[r ^ 1] = of;
        of->maintain();
        maintain();
        if (fa == NULL)
            root = this;
    }
    void splay(Node *dest = NULL) { // 目标节点的父节点
        while (fa != dest) {
            fa->fa->push_down();
            if (fa->fa == dest)
                rotate();
            else if (fa->rel() == rel())
                fa->rotate(), rotate();
            else
                rotate(), rotate();
        }
    }
    int rank() {
        return ch[0] ? ch[0]->size : 0;
    }
};
Node *insert(int x) {
    Node **o = &root, *fa = NULL;
    while (*o && (*o)->x != x) {
        fa = *o;
        ++fa->size;
        o = &fa->ch[x >= fa->x];
    }
    if (*o)
        ++(*o)->cnt, ++(*o)->size;
    else
        *o = new Node(fa, x);
    (*o)->splay();
    return root;
}
Node *find(int x) {
    static Node *o;
    for (o = root; o && o->x != x; o = o->ch[x >= o->x]);
    if (o)
        o->splay();
    return o;
}
int rank(int x) {
    Node *o = find(x);
    if (o)
        return o->rank();
    o = insert(x);
    int res = o->rank();
    erase(o);
    return res;
}
int select(int k) {
    Node *o = root;
    int ork;
    while (true) {
        ork = o->rank();
        if (k < ork)
            o = o->ch[0];
        else if (k >= ork + o->cnt) {
            k -= ork + o->cnt;
            o = o->ch[1];
        } else
            break;
    }
    o->splay();
    return o->x;
}
int n;
void build()
void init() {
    insert(INT_MAX);
    insert(INT_MIN);
    for (i = 1; i <= n; ++i)
        insert(i);
}

int main() {
    static int m, opt, l, r;

    init();
    scanf("%d%d", &n, &m);
    while (m--) {
        scanf("%d%d", &l, &r);
        if (opt == 1)
            insert(x);
        else if (opt == 2)
            erase_x(x);
        else if (opt == 3)
            printf("%d\n", rank(x));
        else if (opt == 4)
            printf("%d\n", select(x));
        else if (opt == 5)
            printf("%d\n", adj(x, 0));
        else if (opt == 6)
            printf("%d\n", adj(x, 1));
    }
    return 0;
}
