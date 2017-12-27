#include <cstdio>
#include <queue>
#include <algorithm>

const int MAXN = 23, MAXS = 1000005;
const char BASE_CHAR = 'a';
const int CHARSET_SIZE = 'z' - BASE_CHAR + 1;

int n, cur, ans;
bool ok[MAXS];

struct Node {
    Node *ch[CHARSET_SIZE], *fail, *next;
    bool is_word;
    int len;
    Node (const bool is = false) : is_word(is), len(0), next(NULL), fail(NULL) {
        for (int i = 0; i < CHARSET_SIZE; ++i)
            ch[i] = NULL;
    }
    void apply() {
        if (cur - len >= 0 && ok[cur - len])
            ok[cur] = true, ans = std::max(ans, cur);
        if (next)
            next->apply();
    }
} *root;

Node *insert(char *s) {
    Node **u = &root;
    char *p;
    for (p = s; *p; ++p) {
        if (!*u)
            *u = new Node;
        u = (*u)->ch + (*p - BASE_CHAR);
    }
    if (!*u)
        *u = new Node(true);
    else
        (*u)->is_word = true;
    (*u)->len = p - s; 
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
    for (cur = 1; s[cur]; ++cur) {
        int in = s[cur] - BASE_CHAR;
        while (u != root && !u->ch[in])
            u = u->fail;
        if (u->ch[in]) {
            u = u->ch[in];
            if (u->is_word)
                u->apply();
            else if (u->next)
                u->next->apply();
            else
                continue;
        } else
            u = root;
    }
}

char text[MAXS], word[15];
int main() {
    root = new Node;
    static int i, m, j;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i) {
        scanf("%s", word);
        insert(word);
    }
    build();
    for (i = 1; i <= m; ++i) {
        ans = 0;
        scanf("%s", text + 1);
        for (j = 1; text[j]; ++j)
            ok[j] = false;
        ok[0] = true;
        exec(text);
        printf("%d\n", ans);
    }

    return 0;
}
