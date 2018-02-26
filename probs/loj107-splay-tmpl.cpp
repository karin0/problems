#include <cstdio>
#include <climits>

struct Node *root;
struct Node {
    Node *fa, *ch[2];
    int x, size, cnt;

    Node(Node *_fa, int _x) : fa(_fa), x(_x), size(1), cnt(1) {}
    int rel() {
        return fa ? (this == fa->ch[1]) : 0;
    }
    void maintain() {
        size = cnt;
        if (ch[0])
            size += ch[0]->size;
        if (ch[1])
            size += ch[1]->size;
    }
    void link(Node *o, Node *p, int r) {
        if (o)
            o->fa = p;
        if (p)
            p->ch[r] = o;
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
    Node *adj(int d) { // 0 for pred, 1 for succ
        static Node *o;
        int rd = d ^ 1;
        for (o = ch[d]; o->ch[rd]; o = o->ch[rd]);
        return o;
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
void erase(Node *o) {
    Node *pre = o->adj(0), *suc = o->adj(1);
    pre->splay();
    suc->splay(pre);
    if (o->size > 1)
        --o->size, --o->cnt;
    else {
        // delete suc->ch[0];
        suc->ch[0] = NULL;
    }
}
void erase_x(int x) {
    Node *o = find(x);
    if (!o)
        return;
    erase(o);
}
int adj(int x, int d) {
    Node *o = find(x);
    if (o)
        return o->adj(d)->x;
    o = insert(x);
    int res = o->adj(d)->x;
    erase(o);
    return res;
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
void init() {
    root = NULL;
    insert(INT_MAX);
    insert(INT_MIN);
}

int main() {
    static int m, opt, x, t;
    init();
    scanf("%d", &m);
    while (m--) {
        scanf("%d%d", &opt, &x);
        if (opt == 0)
            insert(x);
        else if (opt == 1)
            erase_x(x);
        else if (opt == 2)
            printf("%d\n", select(x));
        else if (opt == 3)
            printf("%d\n", rank(x) - 1);
        else {
            t = adj(x, opt - 4);
            if (t == INT_MIN || t == INT_MAX)
                t = -1;
            printf("%d\n", t);
        }
    }
    return 0;
}
