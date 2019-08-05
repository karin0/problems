#include <cstdio>
#include <algorithm>
#include <set>
 
const int N = 300004;
int n;
struct Node {
    Node *fa, *lc, *rc;
    int x, d, tag;
    Node(int _x = 0) : fa(NULL), lc(NULL), rc(NULL), x(_x), d(0), tag(0) {}
    static Node *merge(Node *a, Node *b) {
        if (a == b)
            return a;
        if (!a)
            return b;
        if (!b)
            return a;
        a->push_down(), b->push_down();
        if (a->x < b->x) // 节点的权值不小于其子节点的权值
            std::swap(a, b);
        a->rc = merge(a->rc, b);
        a->rc->fa = a;
        if (!a->lc || (a->rc && a->lc->d < a->rc->d)) // 左子节点的权值不小于右子节点
            std::swap(a->lc, a->rc);
        a->d = a->rc ? a->rc->d + 1 : 0;
        // a->maintain();
        return a;
    }
    void push_down() {
        if (tag) {
            if (lc)
                lc->tag += tag, lc->x += tag;
            if (rc)
                rc->tag += tag, rc->x += tag;
            tag = 0;
        }
    }
    void clear_tag() {
        if (fa)
            fa->clear_tag();
        push_down();
    }
    void remove() {
        clear_tag();
        Node *f = fa, *o = merge(lc, rc);
        if (o)
            o->fa = f;
        if (f) {
            if (f->lc == this)
                f->lc = o;
            else
                f->rc = o;
        }
        /*
        while (f) {
            if (f->lc && f->rc && f->lc->d < f->rc->d)
                std::swap(f->lc, f->rc);
            if ((!f->rc && f->d == 0) || (f->rc && f->d == f->rc->d + 1))
                break;
            f->d = f->rc ? f->rc->d + 1 : 0;
            o = f;
            f = f->fa;
        }*/
    }
    void add(int v) {
        x += v, tag += v;
    }
    Node *find_root();
} g[N];
Node *Node::find_root() {
    static Node *o;
    for (o = this; o->fa; o = o->fa);
    return o;
}
std::multiset<int> ms;
void ms_remove(int v) {
    std::multiset<int>::iterator it = ms.find(v);
    if (it != ms.end())
        ms.erase(it);
}
int main() {
    static int m, i, offset, x, y, v, t;
    static Node *p, *q;
    static char opt[4];
    scanf("%d", &n);
    for (i = 1; i <= n; ++i)
        scanf("%d", &g[i].x), ms.insert(g[i].x);
    scanf("%d", &m);
    while (m--) {
        scanf("%s", opt);
        if (opt[0] == 'U') {
            scanf("%d%d", &x, &y);
            p = g[x].find_root(), q = g[y].find_root();
            if (p != q)
                Node::merge(p, q);
        } else if (opt[0] == 'A') {
            if (opt[1] == '3')
                scanf("%d", &v), offset += v;
            else {
                scanf("%d%d", &x, &v);
                p = g[x].find_root();
                if (opt[1] == '1') {
                    g[x].clear_tag();
                    ms_remove(p->x);
                    t = g[x].x;
                    g[x].remove();
                    g[x] = Node(t + v);
                    ms.insert(Node::merge(p, &g[x])->x);
                } else { // A2
                    t = p->x;
                    p->add(v);
                    ms_remove(t);
                    ms.insert(t + v);
                }
            }
        } else { // F
            if (opt[1] == '3') // ***
                t = *ms.rbegin();
            else {
                scanf("%d", &x);
                if (opt[1] == '1')
                    g[x].clear_tag(), t = g[x].x;
                else
                    t = g[x].find_root()->x;
            }
            printf("%d\n", t + offset);
        }
    }
 
    return 0;
}

