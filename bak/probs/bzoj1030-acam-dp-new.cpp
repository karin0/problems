#include <cstdio>
#include <queue>
 
const int L = 103, N = 60, mo = 10007;
const char BASE_CHAR = 'A';
const int SIGMA = 'Z' - BASE_CHAR + 1;
 
struct Node {
    bool w;
    Node *ch[SIGMA], *fail;
    Node (const bool _w = false) : w(_w), fail(NULL) {
        for (int i = 0; i < SIGMA; ++i)
            ch[i] = NULL;
    }
} pool[N * L], *root;
int ncnt;
Node *new_node(bool w = false) {
    ++ncnt;
    if (w)
        pool[ncnt].w = true;
    return &pool[ncnt];
}
 
Node *insert(char *s) {
    Node *u = root;
    for (char *p = s; *p; ++p) {
        Node *&v = u->ch[*p - BASE_CHAR];
        if (!v)
            v = new_node();
        u = v;
    }
    u->w = true;
    return u;
}
void build() {
    static int i;
    static std::queue<Node *> q;
    root->fail = root;
    for (i = 0; i < SIGMA; ++i) {
        Node *&v = root->ch[i];
        if (v)
            v->fail = root, q.push(v);
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
            v->w |= v->fail->w;
            q.push(v);
        }
    }
}
int pow(int a, int x) {
    static int res;
    for (res = 1; x; a = a * a % mo, x >>= 1)
        if (x & 1)
            res = res * a % mo;
    return res;
}
 
int main() {
    static int n, m, i, j, k, f[L][N * L], ans;
    static char s[L];
    scanf("%d%d", &n, &m);
    root = new_node();
    for (i = 1; i <= n; ++i) {
        scanf("%s", s);
        insert(s);
    }
    build();
    f[0][root - pool] = 1;
    for (i = 0; i < m; ++i)
        for (j = 1; j <= ncnt; ++j)
            if (!pool[j].w)
                for (k = 0; k < SIGMA; ++k)
                    (f[i + 1][pool[j].ch[k] - pool] += f[i][j]) %= mo;
    for (i = 1; i <= ncnt; ++i)
        if (!pool[i].w)
            (ans += f[m][i]) %= mo;
    printf("%d\n", (pow(SIGMA, m) - ans + mo) % mo);
    return 0;
}
