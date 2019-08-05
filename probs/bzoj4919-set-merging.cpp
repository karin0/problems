#include <cstdio>
#include <cctype>
#include <algorithm>
#include <vector>
#include <set>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))

struct IO {
    static const int L = 1000000;
    char a[L], b[L], *s, *t, *p;
    IO() : p(b) {}
    inline char gc() {
        if (s == t)
            t = (s = a) + fread(a, 1, L, stdin);
        return *s++; // return s == t ? -1 : *s++;
    }
    void gs(char *st) {
        static char c;
        for (c = gc(); !isgraph(c); c = gc());
        *st++ = c;
        for (c = gc(); isgraph(c); c = gc())
            *st++ = c;
        *st++ = 0;
    }
    template <class T>
    operator T() {
        static T x;
        static char c;
        static bool neg;
        for (c = gc(); c != '-' && !isdigit(c); c = gc());
        if (c == '-')
            neg = true, c = gc();
        else
            neg = false;
        x = c - '0';
        for (c = gc(); isdigit(c); c = gc())
            x = x * 10 + (c - '0');
        return neg ? -x : x;
    }
    inline void pc(const char c) {
        if (p == b + L)
            fwrite(b, 1, L, stdout), p = b;
        *p++ = c;
    }
    template<class T>
    void print(T x, const bool nl = true) {
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
        if (nl)
            pc('\n');
    }
    void ps(const char *st, const bool nl = true) {
        while (*st)
            pc(*st++);
        if (nl)
            pc('\n');
    }
    inline void flush() const {
        fwrite(b, 1, p - b, stdout); // p = b;
    }
} io;

const int N = 200005;
struct Node {
    int w;
    std::multiset<int> *s;
    std::vector<Node *> adj;
} g[N];
std::multiset<int> *merge(std::multiset<int> *s, std::multiset<int> *t) {
    static std::multiset<int>::iterator it;
    if (s->size() < t->size())
        std::swap(s, t);
    for (it = t->begin(); it != t->end(); ++it)
        s->insert(*it);
    return s;
}
void dfs(Node *const u) {
    for (std::vector<Node *>::iterator v = u->adj.begin(); v != u->adj.end(); ++v) {
        dfs(*v);
        u->s = merge(u->s, (*v)->s);
    }
    std::multiset<int>::iterator it = u->s->lower_bound(u->w);
    if (it != u->s->end())
        u->s->erase(it);
    u->s->insert(u->w);
}

int main() {
    static int n, i;
    n = io;
    rep (i, 1, n) {
        g[i].s = new std::multiset<int>;
        g[i].w = io;
        g[(int)io].adj.push_back(&g[i]);
    }
    dfs(&g[1]);

    io.print((int)g[1].s->size());
    io.flush(); // ***
    return 0;
}
