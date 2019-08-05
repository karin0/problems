#include <cstdio>
#include <climits>
#include <algorithm>

int n;
struct Node *root;
struct Node {
    Node *fa, *ch[2];
    int x, max, add, size; // tag is to add
    bool rev;

    Node(Node *_fa, int _x) : fa(_fa), x(_x), max(0), add(0), size(1), rev(false) {}
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
        push_down();
        size = 1;
        max = x;
        if (ch[0])
            size += ch[0]->size, max = std::max(max, ch[0]->max);
        if (ch[1])
            size += ch[1]->size, max = std::max(max, ch[1]->max);
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
        if (add) {
            if (ch[0])
                ch[0]->add += add, ch[0]->x += add, ch[0]->max += add;
            if (ch[1])
                ch[1]->add += add, ch[1]->x += add, ch[1]->max += add;
            add = 0;
        }
    }
    void rotate() {
        // push_down();
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
    void splay(Node *dest = NULL) {
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
    Node *o = new Node(fa, 0);
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
Node *select_range(int l, int r) {
    static Node *p, *q;
    q = select(r + 1);
    p = select(l - 1);
    p->splay();
    q->splay(p);
    return q->ch[0];
}

int main() {
    static int m, opt, l, r, x;
    static Node *o;
    scanf("%d%d", &n, &m);
    init();
    while (m--) {
        scanf("%d%d%d", &opt, &l, &r);
        o = select_range(l, r);
        if (opt == 1) { // add
            scanf("%d", &x);
            o->add += x, o->x += x, o->max += x; // 及时修改，否则 maintain() 时会使用错误的子树信息
        } else if (opt == 2)
            o->rev ^= 1;
        else
            printf("%d\n", o->max);
    }
    return 0;
}
