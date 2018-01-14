#include <cstdio>
#include <climits>
#include <algorithm>

typedef long long ll;
int n;
ll ssq[100005];
struct Triple {
    ll x[3];
    Triple(ll a = 0, ll b = 0, ll c = 0) {
        x[0] = a, x[1] = b, x[2] = c;
    }
    ll &operator [] (int i) {
        return x[i];
    }
    Triple operator + (Triple &b) {
        return Triple(x[0] + b[0], x[1] + b[1], x[2] + b[2]);
    }
} zeros;
struct Node *root;
struct Node {
    Node *fa, *ch[2];
    int x, pos, tag, size;
    Triple s;
    Node(Node *_fa, int _pos) : fa(_fa), pos(_pos), size(1) {}
    void link(Node *o, Node *p, int r) {
        if (o)
            o->fa = p;
        if (p)
            p->ch[r] = o;
    }
    int rel() {
        return fa && (this == fa->ch[1]);
    }
    void maintain() {
        size = 1, s = Triple(x, (ll)x * pos, (ll)x * pos * pos);
        if (ch[0])
            size += ch[0]->size, s = s + ch[0]->s;
        if (ch[1])
            size += ch[1]->size, s = s + ch[1]->s;
    }
    void add(int d) {
        int l = pos - (ch[0] ? ch[0]->size : 0), r = pos + (ch[1] ? ch[1]->size : 0);
        x += d;
        s[0] += (ll)size * d;
        s[1] += (ll)(l + r) * size / 2 * d;
        s[2] += (ssq[r] - ssq[l - 1]) * d;
        tag += d;
    }
    void push_down() {
        if (tag) {
            if (ch[0])
                ch[0]->add(tag);
            if (ch[1])
                ch[1]->add(tag);
            tag = 0;
        }
    }
    void rotate() {
        Node *f = fa;
        int r = rel();
        link(this, f->fa, f->rel());
        link(ch[r ^ 1], f, r);
        link(f, this, r ^ 1);
        f->maintain();
        maintain();
        if (!fa)
            root = this;
    }
    void splay(Node *dest = NULL) {
        while (fa != dest) {
            if (fa->fa == dest)
                rotate();
            else if (fa->rel() == rel())
                fa->rotate(), rotate();
            else
                rotate(), rotate();
        }
    }
};
Node *select(int k) {
    Node *o = root;
    int ork;
    while (true) {
        o->push_down();
        ork = o->ch[0] ? o->ch[0]->size: 0;
        if (k < ork)
            o = o->ch[0];
        else if (k > ork)
            o = o->ch[1], k -= ork + 1;
        else
            break;
    }
    o->splay();
    return o;
}
Node *build(int l, int r, Node *fa) {
    if (l > r)
        return NULL;
    int mid = (l + r) >> 1;
    Node *o = new Node(fa, mid);
    if (l < r)
        o->ch[0] = build(l, mid - 1, o), o->ch[1] = build(mid + 1, r, o);
    o->maintain();
    return o;
}
Node *locate(int l, int r) {
    static Node *p, *q;
    q = select(r + 1);
    p = select(l - 1);
    p->splay();
    q->splay(p);
    return q->ch[0];
}
ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
    static int m, l, r, x;
    static ll p, q, g;
    static char opt[5];
    static Triple res;
    scanf("%d%d", &n, &m);
    --n;
    for (l = 1; l <= n; ++l)
        ssq[l] = ssq[l - 1] + (ll)l * l;
    root = build(0, n + 1, NULL);
    while (m--) {
        scanf("%s%d%d", opt, &l, &r);
        if (opt[0] == 'C') {
            scanf("%d", &x);
            locate(l, r - 1)->add(x);
        } else {
            res = locate(l, r - 1)->s;
            p = (ll)(r - (ll)l * r) * res[0] + (ll)(l + r - 1) * res[1] - res[2];
            q = (ll)(r - l + 1) * (r - l) / 2;
            g = gcd(p, q);
            printf("%lld/%lld\n", p / g, q / g);

        }
    }

    return 0;
}
