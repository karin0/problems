#include <bits/stdc++.h>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))
#ifdef AKARI
    #define ccc(x) std::cerr << #x " = " << (x) << "  "
    #define ccf(x) std::cerr << #x " = " << (x) << std::endl
    #define cccc(...) fprintf(stderr, __VA_ARGS__)
#else
    #define ccc(x)
    #define ccf(x)
    #define cccc(...)
#endif
struct IO{static const int L=1000000;char a[L],b[L],*s,*t,*p,c;IO():p(b){}~IO(){fwrite(b,1,p-b,stdout);}char gc(){if(s==t)t=(s=a)+fread(a,1,L,stdin);return*s++;}void gs(char*st){for(c=gc();!isgraph(c);c=gc());*st++=c;for(c=gc();isgraph(c);c=gc())*st++=c;*st++=0;}template<class T>operator T(){static T x;static bool neg;for(c=gc();c!='-'&&!isdigit(c);c=gc());if((neg=c=='-'))c=gc();x=c-'0';for(c=gc();isdigit(c);c=gc())x=x*10+(c-'0');return neg?-x:x;}void pc(const char ch){if(p==b+L)fwrite(p=b,1,L,stdout);*p++=ch;}}io;
typedef long long ll;

const int C = 100005, hmo = 1000141;
template <class T, int S>
struct allocator_t {
    T pool[S], *curr;
    void init() {
        curr = pool;  // after doing this, memory allocated by it may not be clean.
    }
    void *operator () () {
        return curr++;
    }
};
int n, m, c;
struct point_t {
    int x, y;
    point_t() {}
    point_t(const int _x, const int _y) : x(_x), y(_y) {}
    bool in_bound() const {
        return 1 <= x && x <= n && 1 <= y && y <= m;
    }
    ll gid() const {
        return (ll)(x - 1) * m + y;
    }
    int hash() const {
        return gid() % hmo;
    }
    bool operator == (const point_t &rh) const {
        return x == rh.x && y == rh.y;
    }
} obs[C], vs[25 * C];
struct map_t {
    struct hnode_t {
        point_t k;
        int v;
        hnode_t *nxt;
        hnode_t() {}
        hnode_t(const point_t _k, hnode_t *const _n) : k(_k), v(0), nxt(_n) {}  // v must be inited
    } *ht[hmo], **toc[hmo];
    allocator_t<hnode_t, 25 * C> pool;
    int tocnt;
    map_t() {
        pool.init();
    }
    int &operator [] (const point_t k) {
        hnode_t *&h = ht[k.hash()];
        for (hnode_t *o = h; o; o = o->nxt)
            if (o->k == k)
                return o->v;
        h = new (pool()) hnode_t(k, h);
        toc[tocnt++] = &h;
        return h->v;
    }
    const hnode_t *find(const point_t k) const {
        for (const hnode_t *o = ht[k.hash()]; o; o = o->nxt)
            if (o->k == k)
                return o;
        return NULL;
    }
    void clear() {
        int i; re (i, 0, tocnt)
            *toc[i] = NULL;
        tocnt = 0;
        pool.init();  // do it
    }
} ht;
struct node_t {
    int dfn, low, bel;
    bool inn;
    struct edge_t *e;
} g[25 * C];
struct edge_t {
    node_t *v;
    edge_t *e;
    edge_t() {}
    edge_t(node_t *_u, node_t *_v) : v(_v), e(_u->e) {
        _u->e = this;
    }
};
allocator_t<edge_t, 100 * C> epool; // ***
void arc(const point_t &u, const int v) { // u has to be checked
    const map_t::hnode_t *it = ht.find(u);
    if (!it || it->v <= 0)
        return;
    new (epool()) edge_t(&g[it->v], &g[v]);
    new (epool()) edge_t(&g[v], &g[it->v]);
}
void dfs1(node_t *u, const int id) {
    u->bel = id;
    for (edge_t *e = u->e; e; e = e->e)
        if (!e->v->bel)
            dfs1(e->v, id);
}
int obel[C];
void dfs2(point_t u, const int uid, const int id) {
    int vid, dx, dy;
    point_t v;
    obel[uid] = id; // ***
    rep (dx, -1, 1) rep (dy, -1, 1) {
        if (dx == 0 && dy == 0)
            continue;
        v = point_t(u.x + dx, u.y + dy);
        if (!v.in_bound())
            continue;
        vid = -ht[v];
        if (vid <= 0 || obel[vid])
            continue;
        dfs2(v, vid, id);
    }
}
int tim;
bool flag;
void tarjan(node_t *u, node_t *f) {
    if (flag)
        return;
    u->low = u->dfn = ++tim;
    node_t *v;
    int ch = 0;
    for (edge_t *e = u->e; e; e = e->e) {
        v = e->v;
        if (v == f)
            continue;
        if (v->dfn)
            u->low = std::min(u->low, v->dfn);
        else {
            ++ch;
            if (u->inn && !f && ch > 1)
                return (void)(flag = true);
            tarjan(v, u);
            u->low = std::min(u->low, v->low);
            if (u->inn && f && u->dfn <= v->low)  // *****
                return (void)(flag = true);
        }
    }
}
bool cmpx(const point_t &p, const point_t &q) {
    return p.x < q.x || (p.x == q.x && p.y < q.y);  // **** use or
}
int solve() {
    static int i, t, vcnt, pid, bcnt, dx, dy, obcnt, oac[C];
    static ll siz;
    static point_t p;
    n = io;
    m = io;
    c = io;
    siz = (ll)n * m;
    if (n == 1 || m == 1) {
        static int a[C];
        if (n == 1) {
            rep (i, 1, c)
                t = io, a[i] = io;
        } else {
            rep (i, 1, c)
                a[i] = io, t = io;
        }
        // check -1 
        if (siz - c < 2)
            return -1;
        if (siz - c == 2) {
            std::sort(a + 1, a + c + 1);
            if (a[1] > 2 || a[c] < siz - 1)
                return -1;  // ****
            rep (i, 2, c) if (a[i] - a[i - 1] > 2)
                return -1;
            return 0;
        }
        // check 1
        if (c == 0)
            return 1;
        t = 1; // ****
        rep (i, 2, c) if (a[i] - a[i - 1] > 1)
            ++t;
        if (t == 0 || (t == 1 && (a[1] == 1 || a[c] == siz)) || (t == 2 && a[1] == 1 && a[c] == siz))   // note t == 0
            return 1;
        return 0;
    }
    rep (i, 1, c)
        obs[i].x = io, obs[i].y = io;
    // check -1
    if (siz - c < 2)
        return -1;
    if (siz - c == 2) {
        static bool cov[C];
        static int x[2], y[2];
        rep (i, 1, siz)
            cov[i] = true;
        rep (i, 1, c)
            cov[obs[i].gid()] = false;
        t = 0;
        rep (i, 1, siz) if (cov[i]) {
            x[t] = i / m + 1;
            y[t] = i % m;
            if (y[t] == 0)
                --x[t], y[t] = m;
            if (++t == 2)
                break;
        }
        if (std::abs(x[0] - x[1]) + std::abs(y[0] - y[1]) == 1)
            return -1;
        return 0;
    }
    if (c == 0)
        return 2; // ***
    // check 0
    ht.clear();
    rep (i, 1, c)
        ht[obs[i]] = -i;
    vcnt = 0; 
    rep (i, 1, c) {
        obel[i] = 0;
        point_t &ob = obs[i];
        rep (dx, -2, 2) rep (dy, -2, 2) {
            if (dx == 0 && dy == 0)
                continue;
            p = point_t(ob.x + dx, ob.y + dy);
            if (!p.in_bound())
                continue;
            int &v = ht[p];
            if (v < 0)
                continue;
            if (v == 0) {
                vs[v = ++vcnt] = p;
                node_t &u = g[v];
                u.inn = false;
                u.dfn = u.low = u.bel = 0;
                u.e = NULL; // do it here
            }
            if (std::abs(dx) <= 1 && std::abs(dy) <= 1)
                g[v].inn = true;  // ***
        }
    }
    epool.init();
    std::sort(vs + 1, vs + vcnt + 1, cmpx);
    rep (i, 1, vcnt) {
        p = vs[i];
        pid = ht[p];
        if (p.x > 1)
            arc(point_t(p.x - 1, p.y), pid);
        if (p.y > 1)
            arc(point_t(p.x, p.y - 1), pid);
    }
    bcnt = 0;
    rep (i, 1, vcnt) if (!g[i].bel)
        dfs1(&g[i], ++bcnt);
    obcnt = 0;
    rep (i, 1, c) if (!obel[i]) {
        dfs2(obs[i], i, ++obcnt);
        oac[obcnt] = 0;
    }
    rep (i, 1, c) {
        point_t &ob = obs[i];
        int &col = oac[obel[i]];
        rep (dx, -1, 1) rep (dy, -1, 1) {
            if (dx == 0 && dy == 0)
                continue;
            p = point_t(ob.x + dx, ob.y + dy);
            if (!p.in_bound() || (t = ht[p]) <= 0)
                continue;
            if (!col)
                col = g[t].bel;
            else if (col != g[t].bel)
                return 0;
        }
    }
    // check 1
    tim = 0;
    flag = false;
    rep (i, 1, vcnt) if (!g[i].dfn) {
        tarjan(&g[i], NULL);
        if (flag)
            return 1;
    }
    return 2;
}
int main() {
    static int ks, i, x;
    ks = io;
    rep (i, 1, ks) {
        x = solve();
        if (x >= 0)
            io.pc('0' + x);
        else
            io.pc('-'), io.pc('1');
        io.pc('\n');
    }
    return 0;
}
