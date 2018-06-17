#include <cstdio>
#include <queue>

const int MAXN = 205, MAXS = 1000005;
const char BASE_CHAR = 'a' - 1;
const int CHARSET_SIZE = 'z' - BASE_CHAR + 1;

struct Node {
    Node *ch[CHARSET_SIZE], *fail, *next;
    bool is_word;
    int cnt;
    Node (const bool is = false) : is_word(is), cnt(0), next(NULL), fail(NULL) {
        for (int i = 0; i < CHARSET_SIZE; ++i)
            ch[i] = NULL;
    }
    void apply() {
        ++cnt;
        if (next)
            next->apply();
    }
} *root;

Node *insert(char *s) {
    Node **u = &root;
    for (char *p = s; *p; ++p) {
        if (!*u)
            *u = new Node;
        u = (*u)->ch + (*p - BASE_CHAR);
    }
    if (!*u)
        *u = new Node(true);
    else
        (*u)->is_word = true;
    return *u;
}
void build() {
    std::queue<Node *> q;
    root->fail = root;
    root->next = NULL;
    q.push(root);
    static int i;
    while (!q.empty()) {
        Node *u = q.front();
        q.pop();
        for (i = 0; i < CHARSET_SIZE; ++i) {
            Node *&v = u->ch[i];
            if (!v) {
                // v = u == root ? root : u->fail->ch[i];
                continue;
            }
            Node *o = u->fail;
            while (o != root && !o->ch[i])
                o = o ->fail;
            v->fail = u != root && o->ch[i] ? o->ch[i] : root;
            v->next = v->fail->is_word ? v->fail : v->fail->next;
            q.push(v);
        }

    }
}
void exec(char *s) {
    Node *u = root;
    for (char *p = s; *p; ++p) {
        char in = *p - BASE_CHAR;
        while (u != root && !u->ch[in])
            u = u->fail;
        if (u->ch[in]) {
            u = u->ch[in];

            if (u->is_word)
                u->apply();
            else if (u->next)
                u->next->apply();
        } else
            u = root;
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
