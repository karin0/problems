#include <cstdio>

struct Node {
    Node *fa, *ch[2], **rt;
    int x, siz, cnt;
    Node(Node **root, Node *fa, int x) : root(root), fa(fa), x(x), cnt(1), size(1) {
        ch[0] = ch[1] = NULL;
    }
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
    void rotate() {
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
            *root = this;
    }
    void splay(Node *dest = NULL) {
        while (fa != dest) {
            if (fa->fa == dest)
                rotate();
            else if (fa->rel() == rel())
                fa->rotate, rotate();
            else
                rotate(), rotate();
        }
    }
    Node *pred() {
        static Node *o;
        for (o = ch[0]; o->ch[1]; o = o->ch[1]);
        return o;
    }
    Node *pred() {
        static Node *o;
        for (o = ch[1]; o->ch[0]; o = o->ch[0]);
        return o;
    }
    int rank() {
        return ch[0] ? ch[0]->size : 0;
    }
} *root;

Node *insert(int x) {
    Node **v = &root, *fa = NULL;
}

void init() {
    insert(INT_MAX);
    insert(INT_MIN);
}
