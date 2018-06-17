#include <bits/stdc++.h>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))
#ifdef AKARI
    #define ccc(x) std::cerr << #x " = " << x << "  "
    #define cccc(x) std::cerr << #x " = " << x << std::endl
    #define ccccc(x) std::cerr << x << std::endl
#else
    #define ccc(x) 0
    #define cccc(x) 0
    #define ccccc(x) 0
#endif

struct IO {
    static const int L = 1000000;
    char a[L], b[L], *s, *t, *p;
    IO() : p(b) {}
    ~IO() {
        fwrite(b, 1, p - b, stdout); /* p = b; */
    }
    char gc() {
        if (s == t)
            t = (s = a) + fread(a, 1, L, stdin);
        return *s++; /* return s == t ? EOF : *s++; */
    }
    void gs(char *st) {
        static char c;
        for (c = gc(); !isgraph(c); c = gc());
        *st++ = c;
        for (c = gc(); isgraph(c); c = gc())
            *st++ = c;
        *st++ = 0;
    }
    void gl(char *st) {
        static char c;
        for (c = gc(); c == '\n' || c == '\r'; c = gc());
        *st++ = c;
        for (c = gc(); c != '\n' && c != '\r'; c = gc())
            *st++ = c;
        *st++ = 0;
    }
    template <class T>
    operator T() {
        static T x;
        static char c;
        static bool neg;
        for (c = gc(); c != '-' && !isdigit(c); c = gc());
        if ((neg = c == '-'))
            c = gc();
        x = c - '0';
        for (c = gc(); isdigit(c); c = gc())
            x = x * 10 + (c - '0');
        return neg ? -x : x;
    }
    void pc(const char c) {
        if (p == b + L)
            fwrite(p = b, 1, L, stdout);
        *p++ = c;
    }
    template<class T>
    void print(T x, const char end = '\n') {
        static char c[30], *q;
        static T y;
        if (x == 0)
            pc('0');
        else {
            if (x < 0)
                pc('-'), x = -x;
            for (q = c; x; x = y)
                y = x / 10, *q++ = x - y * 10 + '0';
            while (q != c)
                pc(*--q);
        }
        if (end)
            pc(end);
    }
    void ps(const char *st, const char end = '\n') {
        while (*st)
            pc(*st++);
        if (end)
            pc(end);
    }
} io;

typedef long long ll;

struct Node *root;
struct Node {
    Node *fa, *ch[2];
    char x;
    int siz;
    bool rev;

    Node(Node *_fa, char _x) : fa(_fa), x(_x), siz(1), rev(false) {}
    static void link(Node *o, Node *p, int r) {
        if (o)
            o->fa = p;
        if (p)
            p->ch[r] = o;
    }
    int rel() {
        return fa ? (this == fa->ch[1]) : 0;
    }
    void maintain() {
        siz = 1;
        if (ch[0])
            siz += ch[0]->siz;
        if (ch[1])
            siz += ch[1]->siz;
    }
    void push_down() {
        if (rev) {
            std::swap(ch[0], ch[1]);
            if (ch[0])
                ch[0]->rev ^= 1;
            if (ch[1])
                ch[1]->rev ^= 1;
            rev = false;
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
        if (fa == NULL)
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
    int rank() {
        return ch[0] ? ch[0]->siz : 0;
    }
};
Node *select(int k) { // find node with rank k
    Node *o = root;
    int ork;
    while (true) {
        o->push_down();
        ork = o->rank();
        if (k < ork)
            o = o->ch[0];
        else if (k > ork) {
            k -= ork + 1;
            o = o->ch[1];
        } else
            break;
    }
    o->splay();
    return o;
}
Node *build(char *l, char *r, Node *fa) {
    if (l > r)
        return NULL;
    char *mid = l + ((r - l) >> 1);
    Node *o = new Node(fa, *mid);
    if (l < r) {
        o->ch[0] = build(l, mid - 1, o); // **
        o->ch[1] = build(mid + 1, r, o);
    }
    o->maintain();
    return o;
}
Node *&select(int l, int r) {
    static Node *p, *q;
    q = select(r + 1);
    p = select(l - 1);
    // p->splay();
    q->splay(p);
    return q->ch[0]; // ->rev ^= 1;
}

int cur;
void insert(int l, char *s) {
    static Node *p, *q;
    // printf("Inserting: %s\n", s);
    if (root) {
        p = select(cur);
        // p->splay();
        q = p->ch[1];
        p->ch[1] = build(s, s + l - 1, p);
        for (p = p->ch[1]; p->ch[1]; p = p->ch[1]);
        p->ch[1] = q;
        q->fa = p;
    } else
        root = build(s - 1, s + l, NULL);
}
void remove(int l) {
    select(cur + 1, cur + l) = NULL;
}
void rotate(int l) {
    select(cur + 1, cur + l)->rev ^= 1;
}
char get() {
    return select(cur + 1)->x;
}
int main() {
    static int m, x;
    static char s[2 * 1024 * 1024 + 10], opt[10];
    m = io;
    while (m--) {
        io.gs(opt);
        switch (opt[0]) {
            case 'M': cur = io; break;
            case 'I': x = io; 
                      io.gl(s + 1);
                      insert(x, s + 1); break; // keep a \n at the begin
            case 'D': remove((int)io); break;
            case 'R': rotate((int)io); break;
            case 'G': io.pc(get());
                      io.pc('\n'); break;
            case 'P': --cur; break;
            default:  ++cur;
        }
    }
    return 0;
}
