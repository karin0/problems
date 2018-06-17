// splay
#include <cstdio>
#include <algorithm>
const int MAXN = 32770, INF = 1000000200;

int n, root;
int val[MAXN], ln = 0; // last_node
int fa[MAXN], ch[MAXN][2];
void link(int o, int x, int d) { // make o the "d" child of x
    if (o) fa[o] = x;
    if (x) ch[x][d] = o;
}
int chd(int o) { // the child-type of o
    return ch[fa[o]][1] == o;
}
void rotate(int o) {
    int x = fa[o], d = chd(o);
    link(o, fa[x], chd(x)); // Diffed
    link(ch[o][d ^ 1], x, d);
    link(x, o, d ^ 1); // Reversing the two makes wrong
    if (x == root) root = o; // Diffed
}
void splay(int o) {
    for (int x; (x = fa[o]); rotate(o)) 
        if (fa[x])
            rotate(chd(o) == chd(x) ? x : o);
}
int add_node(int v) {
    val[++ln] = v;
    return ln;
}
void insert(int o, int v) {
    for (int x; (x = ch[o][v >= val[o]]); o = x);
    link(add_node(v), o, v >= val[o]);
    splay(ln);
}
void init() {
    root = add_node(INF);
    insert(root, -INF); // provide bounds
}
int nb(int o, int d) { // d = 0 for pre, 1 for suf
    o = ch[o][d];
    for (d ^= 1; ch[o][d]; o = ch[o][d]); // Change?
    return val[o];
}

int main() {
    scanf("%d", &n);
    init();
    int i, v, ans = 0, pre, sur;
    for (i = 1; i <= n; ++i) {
        scanf("%d", &v);
        insert(root, v);
        pre = nb(root, 0);
        sur = nb(root, 1);
        ans += ((i == 1) ? v : (std::min(v - pre, sur - v)));
    }
    printf("%d\n", ans);
    return 0;
}
