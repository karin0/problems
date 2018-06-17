#include <cstdio>
#include <queue>

const int MAXN = 205, MAXS = 1000005;
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
    static int n, i;
    static char text[MAXS + MAXN], *p;
    p = text;
    scanf("%d", &n);
    static Node *word[MAXN];
    for (i = 1; i <= n; ++i) {
        scanf("%s", p);
        word[i] = insert(p);
        while (*p)
            ++p;
        *p = BASE_CHAR;
        ++p;
    }
    --p;
    *p = 0;
    build();
    exec(text);
    for (i = 1; i <= n; ++i)
        printf("%d\n", word[i]->cnt);

    return 0;
}
