#include <cstdio>
#include <queue>

const int L = 2000003, N = 100003;
const char BASE_CHAR = 'a' - 1;
const int SIGMA = 'z' - BASE_CHAR + 1;

struct Node {
    Node *ch[SIGMA], *fail, *next;
    bool w;
    int cnt;
    Node (const bool _w = false) : w(_w) {
        for (int i = 0; i < SIGMA; ++i)
            ch[i] = NULL;
    }
    void apply() {
        ++cnt;
        if (next)
            next->apply();
    }
} *root;

Node *insert(char *s) {
    Node *u = root;
    for (char *p = s; *p; ++p) {
        Node *&v = u->ch[*p - BASE_CHAR];
        if (!v)
            v = new Node;
        u = v;
    }
    u->w = true;
    return u;
}
void build() {
    static std::queue<Node *> q;
    static int i;
    root->fail = root;
    root->next = NULL;
    for (i = 0; i < SIGMA; ++i) {
        Node *&v = root->ch[i];
        if (v)
            v->fail = root, v->next = NULL, q.push(v);
        else
            v = root;
    }
    while (!q.empty()) {
        Node *u = q.front();
        q.pop();
        for (i = 0; i < SIGMA; ++i) {
            Node *&v = u->ch[i];
            if (!v) {
                v = u->fail->ch[i];
                continue;
            }
            v->fail = u->fail->ch[i];
            v->next = v->fail->w ? v->fail : v->fail->next;
            q.push(v);
        }
    }
}
void exec(char *s) {
    Node *u = root;
    for (char *p = s; *p; ++p) {
        u = u->ch[*p - BASE_CHAR];

        if (u->w)
            u->apply();
        else if (u->next)
            u->next->apply();
    }
}

int main() {
    root = new Node;
    static int n, m, i, opt, x;
    static char s[L];
    static Node *wd[N];
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%s", s);
        wd[i] = insert(s);
    }
    build();
    scanf("%d", &m);
    while (m--) {
        scanf("%d", &opt);
        if (opt == 1)
            scanf("%s", s), exec(s);
        else {
            scanf("%d", &x);
            printf("%d\n", wd[x]->cnt);
        }
    }
    return 0;
}
