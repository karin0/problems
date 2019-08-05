#include <cstdio>
#include <climits>
#include <algorithm>

int n;
struct Node *root;
struct Node {
    Node *fa, *ch[2];
    int x, size;
    bool rev;

    Node(Node *_fa, int _x) : fa(_fa), x(_x), size(1), rev(false) {}
    void link(Node *o, Node *p, int r) {
        if (o)
            o->fa = p;
        if (p)
            p->ch[r] = o;
    }
    int rel() {
        return fa ? (this == fa->ch[1]) : 0;
    }
    void maintain() {
        size = 1;
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
    int rank() {
        return ch[0] ? ch[0]->size : 0;
    }
    void print() {
        push_down();
        if (ch[0])
            ch[0]->print();
        if (x >= 1 && x <= n)
            printf("%d ",  x);
        if (ch[1])
            ch[1]->print();
    }
};
Node *select(int k) {
    Node *o = root;
    int ork;
    while (true) {
        o->push_down();
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
    Node *o = new Node(fa, mid);
    if (l < r) {
        o->ch[0] = build(l, mid - 1, o); // **
        o->ch[1] = build(mid + 1, r, o);
    }
    o->maintain();
    return o;
}
void init() {
    root = build(0, n + 1, NULL);
}
void reverse(int l, int r) {
    static Node *p, *q;
    q = select(r + 1);
    p = select(l - 1);
    p->splay();
    q->splay(p);
    q->ch[0]->rev ^= 1;
}

int main() {
    static int m, l, r;
    scanf("%d%d", &n, &m);
    init();
    while (m--) {
        scanf("%d%d", &l, &r);
        reverse(l, r);
    }
    root->print();
    return 0;
}
