#include <akari>

IO<31000, 10> io;

cint N = 30002;

struct Node {
    char c;
    int w;
    Node *ch[3];
    Node() {}
    Node(char c) : c(c) {}
} pool[N], *curr = pool;

Node *eval(Node *u, Node *v) {
    int t = u->w + 1;
    re (i, 0, 3) {
        if (u->ch[i])
            t -= u->ch[i]->w;
        else {
            u->ch[i] = v;
            u->w += v->w;
            break;
        }
    }
    Node *o, *x = u->ch[0], *y = u->ch[1], *z = u->ch[2];
    switch (u->c) {
        case 'B':
            if (z) o = eval(x, eval(y, z));
            else return u; break;
        case 'C':
            if (z) o = eval(eval(x, z), y);
            else return u; break;
        case 'K':
            if (y) o = x;
            else return u; break;
        default:
            if (x) o = x;
            else return u;
    }
    o->w += t;
    return o;
}

char s[N];
int sta[N], pre[N];

Node *build(int l, int r) {
    while (s[r] == ')' && pre[r] == l)
        ++l, --r;
    if (l == r)
        return new (curr++) Node(s[l]);
    int p = s[r] == ')' ? pre[r] : r;
    return eval(build(l, p - 1), build(p, r));
}

#ifndef AKARI
    #define FI "combinator"
#endif

int main() {
#ifdef FI
    freopen(FI ".in", "r", stdin);
    freopen(FI ".out", "w", stdout);
#endif

    int n = io.gs(s + 1) - (s + 1), siz = 0;
    rep (i, 1, n) {
        if (s[i] == '(')
            sta[siz++] = i;
        else if (s[i] == ')')
            pre[i] = sta[--siz];
    }
    io << build(1, n)->w daze;
}
