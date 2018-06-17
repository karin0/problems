#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 100005, L = 510005;
const char BC = 'a';
const int SIGMA = 'z' - BC + 1;
struct TrieNode {
    TrieNode *ch[SIGMA];
    struct Node *w;
} *root;
struct Node {
    std::vector<Node *> ch;
    int siz, dfn;
} g[N];
int ncnt;
void insert(char *s) {
    static char *p;
    TrieNode *u = root;
    for (p = s; *p; ++p);
    for (--p; p >= s; --p) {
        TrieNode *&v = u->ch[*p - BC];
        if (!v)
            v = new TrieNode;
        u = v;
    }
    u->w = &g[++ncnt];
}
void build(TrieNode *u, Node *f) {
    if (u->w) {
        if (f)
            f->ch.push_back(u->w);
        for (int i = 0; i < SIGMA; ++i)
            if (u->ch[i])
                build(u->ch[i], u->w);
    } else
        for (int i = 0; i < SIGMA; ++i)
            if (u->ch[i])
                build(u->ch[i], f);
}
void dfs1(Node *u) {
    u->siz = 1;
    for (Node **v = &u->ch.front(); v && v <= &u->ch.back(); ++v) {
        dfs1(*v);
        u->siz += (*v)->siz;
    }
}
bool cmp(const Node *a, const Node *b) {
    return a->siz < b->siz;
}
long long ans; // ***
void dfs2(Node *u, int fdfn) {
    static int tim;
    u->dfn = tim++;
    ans += u->dfn - fdfn;
    if (!u->ch.size())
        return;
    std::sort(u->ch.begin(), u->ch.end(), cmp);
    for (Node **v = &u->ch.front(); v && v <= &u->ch.back(); ++v)
        dfs2(*v, u->dfn);
}

int main() {
    root = new TrieNode;
    root->w = &g[++ncnt];
    static int n, i;
    static char s[L];
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%s", s);
        insert(s);
    }
    build(root, NULL);
    dfs1(root->w);
    dfs2(root->w, 0);
    printf("%lld\n", ans);

    return 0;
}
