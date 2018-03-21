#include <cstdio>
#include <cctype>
#include <algorithm>
#include <vector>
#include <map>
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
        if (neg)
            x = -x;
        return x;
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
    inline void flush() const {
        fwrite(b, 1, p - b, stdout); // p = b;
    }
} io;

const int N = 100002;
struct Node {
    std::map<char, Node *> ch;
    std::vector<int> rec;
    int cnt, maxcnt;
    
    void *operator new (size_t) {
        static Node pool[N * 61], *curr = pool;
        return curr++;
    }
    inline void inc(const int t) {
        ++cnt;
        if (cnt > maxcnt) {
            rec.push_back(t);
            maxcnt = cnt;
        }
    }
} *trie;
void insert(const char s[], const int t) {
    static Node *o;
    static const char *p;
    static int c;
    o = trie;
    // o->inc(t);
    for (p = s; *p; ++p) {
        c = *p - 'a';
        if (!o->ch.count(c))
            o->ch[c] = new Node;
        o = o->ch[c];
        o->inc(t);
    }
}
void erase(const char s[]) {
    static Node *o;
    static const char *p;
    o = trie;
    // --o->cnt;
    for (p = s; *p; ++p) {
        o = o->ch[*p - 'a'];
        --o->cnt;
    }
}
int query(const char s[], const int k) {
    static Node *o;
    static const char *p;
    static int c;
    o = trie;
    for (p = s; *p; ++p) {
        c = *p - 'a';
        if (!o->ch.count(c))
            return -1;
        o = o->ch[c];
    }
    return k < o->maxcnt ? o->rec[k] : -1;
}

int main() {
    static int m, op, a, b, c, la, i;
    static char s[70];
    m = io;
    trie = new Node;
    rep (i, 1, m) {
        op = io;
        io.gs(s);
        switch (op) {
            case 1: 
                insert(s, i);
                break;
            case 2: 
                erase(s);
                break;
            default: 
                a = io, b = io, c = io;
                io.print(la = query(s, ((long long)a * la + b) % c));
                if (la == -1)
                    la = 1;
        }
    }

    io.flush(); // ***
    return 0;
}
