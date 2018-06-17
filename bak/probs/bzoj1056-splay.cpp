#include <cstdio>
#include <cctype>
#include <climits>

struct Data {
    int x, ord;
    Data(int _x, int _ord) : x(_x), ord(_ord) {}
    bool operator < (const Data &o) {
        if (x == o.x)
            return ord < o.ord;
        else
            return x > o.x;
    }
    bool operator >= (const Data &o) {
        return !(*this < o);
    }
};
struct Node *root;
struct Node {
    Node *fa, *ch[2];
    Data x;
    int ha, size;

    Node(Node *_fa, Data _x) : fa(_fa), x(_x), size(1) {}
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
Node *insert(Data x) {
    Node **o = &root, *fa = NULL;
    while (*o) {
        fa = *o;
        ++fa->size;
        o = &fa->ch[x >= fa->x];
    }
    *o = new Node(fa, x);
    (*o)->splay();
    return root;
}
void erase(Node *o) {
    o->splay();
    Node *pre = o->adj(0), *suc = o->adj(1);
    pre->splay();
    suc->splay(pre);
    // delete suc->ch[0];
    suc->ch[0] = NULL;
    suc->maintain();
    pre->maintain();
}
Node *select(int k) {
    Node *o = root;
    int ork;
    while (true) {
        ork = o->rank();
        if (k < ork)
            o = o->ch[0];
        else if (k > ork) {
            k -= ork + 1;
            o = o->ch[1];
        } else
            break;
    }
    o->splay();
    return o;
}
void init() {
    root = NULL;
    insert(Data(INT_MAX, INT_MAX));
    insert(Data(INT_MIN, INT_MIN));
}

int toint(char *s) {
    static int res;
    for (res = 0; *s; ++s)
        res = res * 10 + *s - '0';
    return res;
}

const char BASE_CHAR = 'A';
const int SIGMA = 'Z' - BASE_CHAR + 1;
int ucnt;
struct TrieNode {
    TrieNode *ch[SIGMA];
    int no;
    TrieNode(int _i = 0) : no(_i) {}
} *trie;
int insert(char *s) {
    TrieNode **o = &trie;
    for (; *s; ++s) {
        if (!*o)
            *o = new TrieNode;
        o = (*o)->ch + *s - BASE_CHAR;
    }
    if (!*o)
        *o = new TrieNode(++ucnt);
    else if (!(*o)->no)
        (*o)->no = ++ucnt;
    return (*o)->no;
}

const int MAXN = 250005;
Node *pos[MAXN];
char req[MAXN][15];

int main() {
    static int m, x, ha, tim, i;
    static Node *o;
    scanf("%d", &m);
    init();
    for (tim = 0; tim < m; ++tim) {
        scanf("%s", req[tim]);
        if (req[tim][0] == '+') {
            scanf("%d", &x);
            ha = insert(req[tim] + 1);
            if (pos[ha])
                erase(pos[ha]);
            pos[ha] = insert(Data(x, tim));
        } else if (isdigit(req[tim][1])) {
            x = toint(req[tim] + 1);
            for (i = 0; i <= 9; ++i) {
                o = select(x + i);
                if (o->x.x == INT_MIN)
                    break;
                if (i > 0)
                    putchar(' ');
                printf("%s", req[o->x.ord] + 1);
            }
            putchar('\n');
        } else {
            ha = insert(req[tim] + 1);
            o = pos[ha];
            o->splay();
            printf("%d\n", o->rank());
        }
    }
    return 0;
}
