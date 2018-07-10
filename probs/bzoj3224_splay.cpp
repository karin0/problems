#include <cstdio>
const int MAXN = 100000;
int root;
int val[MAXN], ln;
int fa[MAXN], ch[MAXN][2], cnt[MAXN], siz[MAXN];
void link(int o, int x, int d) {
    if (o) fa[o] = x;
    if (x) ch[x][d] = o;
}
int chd(int o) {
    return ch[fa[o]][1] == o;
}
void push(int o) {
    siz[o] = siz[ch[o][0]] + siz[ch[o][1]] + cnt[o];
}
void rotate(int o) {
    int x = fa[o], d = chd(o);
    link(o, fa[x], chd(x));
    link(ch[o][d ^ 1], x, d);
    link(x, o, d ^ 1);
    push(x);
    push(o);
    if (x == root) root = o;
}
int add_node(int v) {
    val[++ln] = v;
    cnt[ln] = 1;
    siz[ln] = 1;
    return ln;
}
void insert(int o, int v) {
    for (int x; x = ch[o][v >= val[o]]; o = x)
}

int main() {
    int q, opt, x;
    scanf("%d", &q);
    while (--q) {
        scanf("%d%d", &opt, &x);
        if (opt == 1) {
            if (ln) insert(x);
            else root = add_node(x);
        }
        else if (opt == 2) remove(x);
        else if (opt == 3) printf("%d\n", rank(x));
        else if (opt == 4) printf("%d\n", kth(x));
        else printf("%d\n", nb(x, opt - 5));
    }
    return 0;
}
