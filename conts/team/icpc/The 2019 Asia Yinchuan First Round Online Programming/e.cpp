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
#define asser(...) 0

const int N = 5004;
struct Node *curr, *rt;
struct Node {
    int len, val[3];
    Node *ch[4], *fa;
    Node() {}
    Node(int x, Node *c1, Node *c2) : len(1) {
        val[0] = x;
        val[1] = val[2] = 0;
        ch[0] = c1;
        ch[1] = c2;
        ch[2] = ch[3] = fa = NULL;
        if (c1) c1->fa = this;
        if (c2) c2->fa = this;
    }
    void clear() {
        len = 0;
        fa = ch[0] = ch[1] = ch[2] = ch[3] = NULL;
        val[0] = val[1] = val[2] = 0;
    }
    void insert(int x) {
        ccc(x, len, val[0], val[1], val[2]);
        if (!ch[0] && len < 3) {
            if (len == 0)
                val[0] = x;
            else if (len == 1) {
                if (x < val[0])
                    val[1] = val[0], val[0] = x;
                else
                    val[1] = x;
            } else {
                asser(len == 2);
                if (x < val[0])
                    val[2] = val[1], val[1] = val[0], val[0] = x;
                else if (x < val[1])
                    val[2] = val[1], val[1] = x;
                else
                    val[2] = x;
            }
            ++len;
            return;
        }
        if (len == 3) {
            Node *p = new (curr++) Node(val[0], ch[0], ch[1]);
            Node *q = new (curr++) Node(val[2], ch[2], ch[3]);
            if (fa) {
                Node **fch = fa->ch;
                int *fv = fa->val;
                p->fa = q->fa = fa;
                if (fch[0] == this) {
                    fv[2] = fv[1];
                    fv[1] = fv[0];
                    fv[0] = val[1];
                    fch[3] = fch[2];
                    fch[2] = fch[1];
                    fch[1] = q;
                    fch[0] = p;
                } else if (fch[1] == this) {
                    fv[2] = fv[1];
                    fv[1] = val[1];
                    fch[3] = fch[2];
                    fch[2] = q;
                    fch[1] = p;
                } else {
                    asser(fch[2] == this);
                    fv[2] = val[1];
                    fch[3] = q;
                    fch[2] = p;
                }
                ++fa->len; // *
            } else
                rt = new (curr++) Node(val[1], p, q);
                // rt->insert(x);
            if (x < val[1])
                return p->insert(x);
            else
                return q->insert(x);
        }
        re (i, 0, len)
            if (x < val[i])
                return ch[i]->insert(x);
        return ch[len]->insert(x);
    }
    void dfs() {
        re (i, 0, len - 1)
            printf("%d ", val[i]);
        printf("%d\n", val[len - 1]);
        rep (i, 0, len)
            if (ch[i])
                ch[i]->dfs();
    }
    /*
    void mdfs() {
        rep (i, 0, len) {
            if (ch[i])
                ch[i]->mdfs();
            if (i < len)
                printf("%d / %d [ %d ]\n", i, len, val[i]);
        }
    }
    */
} pool[N * 3];

int main() {
    int T;
    scanf("%d", &T);
    rep (ks, 1, T) {
        rt = pool;
        rt->clear();
        curr = pool + 1;
        int n;
        scanf("%d", &n);
        rep (i, 1, n) {
            int x;
            scanf("%d", &x);
            rt->insert(x);
        }
        printf("Case #%d:\n", ks);
        rt->dfs();
    }
}
