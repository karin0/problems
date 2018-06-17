// a bad version. wa.
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 1203, M = 100, L = 1503, mo = 1000000007;
const char BASE_CHAR = '0';
const int SIGMA = '9' - BASE_CHAR + 1;
struct Node {
    bool w;
    Node *ch[SIGMA], *fail;
    Node (const bool _w = false) : w(_w), fail(NULL) {
        for (int i = 0; i < SIGMA; ++i)
            ch[i] = NULL;
    }
} pool[M * L], *root;
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
int num[N];
int len, f[N][L][2][2];

int dp(int w, int o, bool lim, bool all0) {
    // printf("%d, %d, %d, %d\n", w, o, lim, all0);
    if (w < 0)
        return !all0;
    int &ans = f[w][o][lim][all0];
    if (ans != -1)
        return ans;
    ans = 0;
    for (int i = 0; i <= (lim ? num[w] : 9); ++i)
        if (all0 && (i == 0))
            (ans += dp(w - 1, root - pool, lim && (i == num[w]), true)) %= mo;
    
        else if (!pool[o].ch[i]->w)
            (ans += dp(w - 1, pool[o].ch[i] - pool, lim && (i == num[w]), false)) %= mo;
    return ans;
}
int main() {
    static int m, i, ans, o;// all0, w, lim;
    static char s[L];
    // static Node *v;
    root = new_node();
    scanf("%s%d", s, &m);
    len = strlen(s);
    --len;
    for (i = 0; i <= len; ++i)
        num[i] = s[len - i] - '0';
    //len;
    /*
    i = 0;
    while (i < len && num[i] == 9)
        num[i++] = 0;
    if (i == len)
        ++len;
    ++num[i];*/
    for (i = 1; i <= m; ++i) {
        scanf("%s", s);
        insert(s);
    }
    build();
    memset(f, -1, sizeof(f));
    for (i = 0; i <= num[len]; ++i)
        if (!root->ch[i]->w)
            ans += dp(len - 1, root->ch[i] - pool, i == num[len], i == 0);
    /*
    f[0][root - pool][1][1] = 1;
    for (w = 0; w <= len; ++w) {
        for (lim = 0; lim <= 1; ++lim) {
            for (all0 = 0; all0 <= 1; ++all0) {
                for (o = 1; o <= ncnt; ++o) {
                    if (!pool[o].w) {
                        for (i = 0; i <= (lim ? num[w + 1] : 9); ++i) {
                            if (all0 && (i == 0))
                                v = root;
                            else {
                                v = &pool[o];
                                while (v != root && !v->ch[i])
                                    v = v->fail;
                                v = v->ch[i];
                            }
                            (f[w + 1][v - pool][lim && i == num[w + 1]][all0 && (i == 0)] += f[w][o][lim][all0]) %= mo;
                        }
                    }
                }
            }
        }
    }*/
    /*
    for (o = 1; o <= ncnt; ++o)
        if (!pool[o].w) {
            (ans += f[len][o][0][0]) %= mo;
            (ans += f[len][o][0][1]) %= mo;
        }*/
    printf("%d\n", ans);
    return 0;
}
