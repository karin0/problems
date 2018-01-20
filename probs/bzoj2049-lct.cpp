#include <cstdio>
#include <climits>
#include <algorithm>

const int N = 10010;
struct LinkCutTree {
    struct Node {
        Node *ch[2], *fa, *path_fa;
        bool rev;

        Node() : fa(NULL), path_fa(NULL), rev(false) {}
        static void link(Node *o, Node *p, const int r) {
            if (o)
                o->fa = p;
            if (p)
                p->ch[r] = o;
        }
        int rel() {
            return fa ? this == fa->ch[1] : 0;
        }
        //void maintain() {
        //
        //}
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
            if (fa->fa)
                fa->fa->push_down();
            fa->push_down();
            push_down();

            Node *f = fa;
            int r = rel();
            link(this, f->fa, f->rel());
            link(ch[r ^ 1], f, r);
            link(f, this, r ^ 1);
            // f->maintain();
            // maintain();
            std::swap(path_fa, f->path_fa);
        }
        void splay() {
            while (fa) {
                if (fa->fa)
                    fa->fa->push_down();
                fa->push_down();
                push_down();
                if (fa->fa == NULL)
                    rotate();
                else if (fa->rel() == rel())
                    fa->rotate(), rotate();
                else
                    rotate(), rotate();
            }
            push_down();
        }
        
        void expose() { // 将当前节点置为其所在路径的下端，即切断自该节点向下的部分路径
            splay();
            push_down();
            if (ch[1]) {
                ch[1]->fa = NULL;
                ch[1]->path_fa = this;
                ch[1] = NULL;
                // maintain();
            }
        }
        bool splice() { // 将当前节点所在的路径与其尾部节点的父节点所在的路径合并，即实现了路径的向上延长
            splay();
            if (!path_fa)
                return false;
            path_fa->expose();
            path_fa->ch[1] = this;
            fa = path_fa;
            path_fa = NULL;
            // fa->maintain();
            return true;
        }
        void access() { // 被访问的节点会与根节点之间以路径相连，并且该节点为路径最下端
            for (expose(); splice(); );
        }
        void evert() { // 将节点置为其所在树的根节点，该操作等价于把该节点到根节点所经过的所有边方向取反；
            access();
            splay();
            rev ^= 1;
        }
        Node *find_root() {
            static Node *o;
            access();
            splay();
            for (o = this; o->ch[0]; o->push_down(), o = o->ch[0]);
            return o;
        }
    } *g[N];
    void link(Node *u, Node *v) { // 将节点 u 和 v 连接，执行操作后 u 成为 v 的父节点
        v->evert();
        v->path_fa = u;
    }
    void cut(Node *u, Node *v) { // 将节点 u 和 v 分离，执行操作后 v 及其子节点组成单独的一棵树
        u->evert();
        v->access();
        v->splay();

        v->push_down();
        v->ch[0]->fa = NULL;
        v->ch[0] = NULL;
        // v->maintain();
    }
    Node *make_tree() {
        return new Node;    
    }
} lct;

int main() {
    static int n, m, i, u, v;
    static char opt[10];
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i)
        lct.g[i] = lct.make_tree();
    while (m--) {
        scanf("%s%d%d", opt, &u, &v);
        if (opt[0] == 'C')
            lct.link(lct.g[u], lct.g[v]);
        else if (opt[0] == 'D')
            lct.cut(lct.g[u], lct.g[v]);
        else if (opt[0] == 'Q')
            puts(lct.g[u]->find_root() == lct.g[v]->find_root() ? "Yes" : "No");
    }
    return 0;
}
