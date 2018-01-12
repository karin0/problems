#include <cstdio>
#include <climits>
#include <algorithm>

int n, a[100005];
struct Node *root;
struct Node {
    Node *fa, *ch[2], *vall;
    int x, min, size; // tag is to add
    bool rev;

    Node(Node *_fa, int _x) : fa(_fa), vall(this), x(_x), min(_x), size(1), rev(false) {}
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
        vall = this;
        if (ch[0]) {
            size += ch[0]->size;
            if (ch[0]->min < min)
                min = ch[0]->min, vall = ch[0]->vall;
        }
        if (ch[1]) {
            size += ch[1]->size;
            if (ch[1]->min < min)
                min = ch[1]->min, vall = ch[1]->vall;
        }
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
    void update() {
        static Node *o;
        for (o = this; o; o = o->fa)
            o->maintain();
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
    Node *o = new Node(fa, a[mid]);
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
    static int i, rk;
    static Node *o;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i)
        scanf("%d", a + i);
    a[0] = a[n + 1] = INT_MAX;
    init();
    for (i = 0; i < n; ++i) {
        o = root->vall;
        // printf("%d: %d\n", i, o->x);
        o->splay();
        o->push_down();
        rk = o->rank();
        printf("%d ", rk + i);
        o = select_range(rk, rk);
        o->fa->ch[0] = NULL;
        o->fa->update();
        if (rk > 1)
            select_range(1, rk - 1)->rev ^= 1;
    }
    return 0;
}
