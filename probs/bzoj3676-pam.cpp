#include <akari>
IO<1000000, 1000000> io;

cint N = 300003, sig = 'z' - 'a' + 1;

struct PAM {
    struct Node {
        Node *ch[sig], *fail;
        int cnt, len;
        Node() {}
        Node(cint l) : len(l) {}
    } *rt[2], *last, pool[N + 2], *curr;
    char s[N];
    int siz;
    PAM() {
        curr = pool;
        last = rt[0] = new (curr++) Node;
        last->fail = rt[1] = new (curr++) Node(-1);
        rt[1]->fail = rt[1];
        s[siz = 0] = -1;
    }
    Node *get_fail(Node *o) {
        while (s[siz - o->len - 1] != s[siz])
            o = o->fail;
        return o;
    }
    // Extend!
    void extend(cchar c) {
        s[++siz] = c;
        Node *o = get_fail(last);
        Node *&p = o->ch[c];
        if (!p) {
            p = new (curr++) Node(o->len + 2);
            p->fail = o == rt[1] ? rt[0] : get_fail(o->fail)->ch[c];
        }
        ++p->cnt;
        last = p;
    }
    // Watashi wa tsuyoi sugi.
    /* void count() {
        for (Node *o = curr - 1; o >= pool; --o)
            o->fail->cnt += o->cnt;
    } */
    void insert(cchar *p) {
        while (*p) extend(*p++ - 'a');
    }
    ll solve() {
        // count();
        ll res = 0;
        for (Node *o = curr - 1; o >= pool; --o) {
            o->fail->cnt += o->cnt;
            res = std::max(res, (ll)o->cnt * o->len);
        }
        return res;
    }
} pam;
char s[N];
int main() {
    io >> s;
    pam.insert(s);
    io << pam.solve() daze;
}
