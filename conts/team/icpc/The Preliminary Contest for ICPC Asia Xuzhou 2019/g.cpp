#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)
typedef long long ll;
typedef const int cint;

#ifdef AKARI
void cca() {
    std::cerr << "\033[39;0m" << std::endl;
}
template <typename T, typename... Args>
void cca(T a, Args... args) {
    std::cerr << a << ", ";
    cca(args...);
}
    #define ccc(args...) std::cerr << "\033[32;1m" << #args << "  =  ", cca(args)
    #define ccf(args...) fprintf(stderr, args)
    #define crep(i_, s_, t_) rep(i, s_, t_)
#else
    #define ccc(...) 0
    #define ccf(...) 0
    #define crep(...) if (0)
#endif

typedef const char cchar;
cint N = 300003, sig = 'z' - 'a' + 1;

struct PAM {
    struct Node {
        Node *ch[sig], *fail;
        bool vis[sig];
        int f, cnt, len;
        Node() {}
        Node(cint l) : len(l) {}
    } *rt[2], *last, pool[N + 2], *curr;
    char s[N];
    int siz;
    PAM() {
        curr = pool;
        last = rt[0] = new (curr++) Node;
        last->fail = rt[1] = new (curr++) Node(-1);
        rt[1]->fail = rt[1];
        s[siz = 0] = -1;
    }
    Node *get_fail(Node *o) {
        while (s[siz - o->len - 1] != s[siz])
            o = o->fail;
        return o;
    }
    void extend(int c) {
        ccc((char)(c + 'a'));
        s[++siz] = c;
        Node *o = get_fail(last);
        Node *&p = o->ch[c];
        if (!p) {
            p = new (curr++) Node(o->len + 2);
            p->fail = o == rt[1] ? rt[0] : get_fail(o->fail)->ch[c];

            re (i, 0, 26) if (o->vis[i])
                p->vis[i] = true;
            p->f = o->f;
        }
        ++p->cnt;
        if (!p->vis[c])
            ++p->f;
        p->vis[c] = true;
        last = p;
    }
    void insert(cchar *p) {
        while (*p) extend(*p++ - 'a');
    }
    ll solve() {
        ll res = 0;
        for (Node *o = curr - 1; o >= pool; --o) {
            ccc(o->cnt, o->f, o->len);
            o->fail->cnt += o->cnt;
            res += (ll)o->cnt * o->f;
        }
        return res;
    }
} pam;
ll calc(cchar *s) {
    static bool vis[300];
    int n = std::strlen(s);
    ll ans = 0;
    --s;
    rep (i, 1, n) rep (j, i, n) {
        bool ok = true;
        for (int x = i, y = j; x <= y; ++x, --y) {
            if (s[x] != s[y]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            rep (t, 'a', 'z')
                vis[t] = false;
            rep (t, i, j) if (!vis[s[t]]) {
                vis[s[t]] = true;
                ++ans;
            }
        }
    }
    return ans;
}
char s[N];
int main() {
    scanf("%s", s);
    pam.insert(s);
    printf("%lld\n", pam.solve());
    // ccc(calc(s));
}
