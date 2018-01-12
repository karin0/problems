#include <cstdio>
#include <climits>
#include <algorithm>

const int MAXN = 100010;
int n, a[MAXN];
struct Node *root;
struct Node {
    Node *fa, *ch[2];
    int x, min, add, size;
    bool rev;

    Node(Node *_fa, int _x) : fa(_fa), x(_x), min(_x), add(0), size(1), rev(false) {}
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
        min = x;
        if (ch[0])
            size += ch[0]->size, min = std::min(min, ch[0]->min);
        if (ch[1])
            size += ch[1]->size, min = std::min(min, ch[1]->min);
    }
    void reverse() {
        rev ^= 1;
    }
    void push_down() {
        if (rev) {
            std::swap(ch[0], ch[1]);
            if (ch[0])
                ch[0]->reverse();
            if (ch[1])
                ch[1]->reverse();
            rev = false;
        }
        if (add) {
            if (ch[0])
                ch[0]->add += add, ch[0]->x += add, ch[0]->min += add;
            if (ch[1])
                ch[1]->add += add, ch[1]->x += add, ch[1]->min += add;
            add = 0;
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
    void cut() {
        if (fa)
            fa->ch[rel()] = NULL;
    }
    int rank() {
        return ch[0] ? ch[0]->size : 0;
    }
    void update() {
        static Node *o;
        for (o = this; o; o = o->fa)
            o->maintain();
    }
    void clear() {
        if (fa)
            fa->clear();
        push_down();
    }
};
void link(Node *o, Node *p, int r) {
    if (o)
        o->fa = p;
    if (p)
        p->ch[r] = o;
}
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
    Node *o = new Node(fa, a[mid]);
    if (l < r) {
        o->ch[0] = build(l, mid - 1, o); // **
        o->ch[1] = build(mid + 1, r, o);
    }
    o->maintain();
    return o;
}
void init() {
    root = build(0, n + 3, NULL); // 2 .. n + 1 <- 1 .. n
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
    static int m, i, l, r, x;
    static char opt[10];
    static Node *o, *p;
    scanf("%d", &n);
    for (i = 2; i <= n + 1; ++i)
        scanf("%d", a + i);
    init();
    scanf("%d", &m);
    while (m--) {
        scanf("%s", opt);
        if (opt[0] == 'A') { // add
            scanf("%d%d%d", &l, &r, &x);
            ++l, ++r;
            o = select_range(l, r);
            o->add += x, o->x += x, o->min += x;
            o->update();
        } else if (opt[0] == 'M') { // query min
            scanf("%d%d", &l, &r);
            ++l, ++r;
            printf("%d\n", select_range(l, r)->min);
        } else if (opt[0] == 'I') { // insert
            scanf("%d%d", &i, &x);
            ++i;
            o = select_range(i, i);
            o->push_down(); // *** 选出的区间（子树）可能有标记
            o->ch[1] = new Node(o, x);
            o->update();
            /*
            Node *p, *q;
            p = select(i);
            q = select(i + 1);
            p->splay();
            q->splay(p);
            q->ch[0] = new Node(q, x);
            q->update();*/ // 无需删除标记
        } else if (opt[0] == 'D') { // delete
            scanf("%d", &i);
            ++i;
            o = select_range(i, i);
            o->cut();
            o->fa->update();
        } else if (opt[3] == 'E') { // reverse
            scanf("%d%d", &l, &r);
            ++l, ++r;
            select_range(l, r)->reverse();
        } else { // revolve : 剪切右 x 个到左边
            scanf("%d%d%d", &l, &r, &x);
            ++l, ++r;
            x %= r - l + 1;
            if (x == 0)
                continue;
            o = select_range(r - x + 1, r);
            o->push_down();
            o->cut();
            p = select_range(l - 1, l - 1);
            p->push_down();
            link(o, p, 1);
            p->update();
            /*
            select_range(l, r)->reverse();
            select_range(l, l + x - 1)->reverse();
            select_range(l + x, r)->reverse();*/
        }
    }
    return 0;
}
