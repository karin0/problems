#include <cstdio>
#include <algorithm>
#include <iostream>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)
typedef long long ll;
typedef const int cint;

#ifdef AKARIn
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

const int N = 1003;
struct Node {
    int siz;
    Node *ch[2];
    Node() {}
    Node(bool) : siz(0) { ch[0] = ch[1] = NULL; }
} pool[N * 31], *curr, *trie = pool;

int dep;
void ins(int x) {
    ccc("ins", x);
    Node *o = trie;
    ++o->siz;
    per (i, dep, 0) {
        bool v = (x >> i) & 1;
        if (!o->ch[v])
            o->ch[v] = new (curr++) Node(true);
        o = o->ch[v];
        ++o->siz;
    }
}
void del(int x) {
    ccc("del", x);
    Node *o = trie;
    --o->siz;
    per (i, dep, 0) {
        bool v = (x >> i) & 1;
        o = o->ch[v];
        --o->siz;
    }
}
int qry(int x) {
    Node *o = trie;
    if (!o->siz)
        return 0;
    int ans = 0;
    per (i, dep, 0) {
        bool v = ((x >> i) & 1 )^ 1;
        // ccc(x, i, v, ans);
        if (o->ch[v] && o->ch[v]->siz) {
            o = o->ch[v];
            ccc("go", v, "at", i, (x>>i)&1);
            ans |= 1 << i;
        } else if (o->ch[v ^ 1] && o->ch[v ^ 1]->siz)
            o = o->ch[v ^ 1], ccc("go", v ^ 1, "at", i, (x>>i)&1);
        else {
            ccc(ans, "quit");
            return ans;
        }
        ccc(i, o->siz, ans);
    }
    ccc(ans);
    return ans;
    }

int a[N];
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        curr = trie + 1;
        trie->siz = 0;
        trie->ch[0] = trie->ch[1] = NULL;
        int n, mx = 0;
        scanf("%d", &n);
        rep (i, 1, n) {
            scanf("%d", &a[i]);
            mx = std::max(mx, a[i]);
        }
        for (dep = 0; (1 << dep) < mx; ++dep);
        ++dep;
        ccc(dep);
        rep (i, 1, n)
            ins(a[i]);
        int ans = 0;
        rep (i, 1, n)  {
            del(a[i]);
            re (j, 1, i) {
                del(a[j]);
                ans = std::max(ans, qry(a[i] + a[j]));
                ins(a[j]);
            }
            ins(a[i]);
        }
        printf("%d\n", ans);
    }
}