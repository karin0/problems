#include <cstdio>
#include <queue>
 
const int L = 103, N = 60, mo = 10007;
const char BASE_CHAR = 'A';
const int SIGMA = 'Z' - BASE_CHAR + 1;
 
struct Node {
    bool is_word;
    Node *ch[SIGMA], *next, *fail;
    Node (const bool _w = false) : is_word(_w), next(NULL), fail(NULL) {
        for (int i = 0; i < SIGMA; ++i)
            ch[i] = NULL;
    }
} pool[N * L], *root;
int ncnt;
Node *new_node(bool w = false) {
    ++ncnt;
    if (w)
        pool[ncnt].is_word = true;
    return &pool[ncnt];
}
 
Node *insert(char *s) {
    Node **u = &root;
    for (char *p = s; *p; ++p) {
        if (!*u)
            *u = new_node();
        u = (*u)->ch + (*p - BASE_CHAR);
    }
    if (!*u)
        *u = new_node(true);
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
        for (i = 0; i < SIGMA; ++i) {
            Node *v = u->ch[i];
            if (!v) {
                // u->ch[i] = u == root ? root : u->fail->ch[i];
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
bool next(Node *u, int c, Node *&v) {
    while (u != root && !u->ch[c])
        u = u->fail;
    v = u->ch[c] ? u->ch[c] : root;
    if (!u->ch[c])
        return false;
    if (v->is_word || v->next)
        return true;
    return false;
}
int pow(int a, int x) {
    static int res;
    for (res = 1; x; a = a * a % mo, x >>= 1)
        if (x & 1)
            res = res * a % mo;
    return res;
}
 
int main() {
    static int n, m, i, j, k, f[L][N * L];
    static char s[L];
    static Node *v;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i) {
        scanf("%s", s);
        insert(s);
    }
    build();
    for (j = 1; j <= ncnt; ++j)
        f[0][j] = 1;
    for (i = 1; i <= m; ++i)
        for (j = 1; j <= ncnt; ++j)
            for (k = 0; k < SIGMA; ++k) {
                if (!next(&pool[j], k, v))
                    (f[i][j] += f[i - 1][v - pool]) %= mo;
            }
    printf("%d\n", (pow(SIGMA, m) - f[m][root - pool] + mo) % mo);
    return 0;
}
