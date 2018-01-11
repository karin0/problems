#include <cstdio>

const int SIGMA = 4;

struct Node {
    Node *ch[SIGMA], *next;
    int max;
    Node(int x) : next(NULL), max(x) {}
} *start, *last;
void init() {
    start = last = new Node(0);
}
Node *extend(int c) {
    static Node *u, *o, *p, *q;
    static int i;
    u = new Node(last->max + 1);
    o = last;
    for (; o && !o->ch[c]; o = o->next)
        o->ch[c] = u;
    if (!o)
        u->next = start;
    else if (o->ch[c]->max == o->max + 1)
        u->next = o->ch[c];
    else {
        p = o->ch[c];
        q = new Node(o->max + 1);
        for (i = 0; i < SIGMA; ++i)
            q->ch[i] = p->ch[i];
        q->next = p->next;
        p->next = u->next = q;
        for (; o && o->ch[c] == p; o = o->next)
            o->ch[c] = q; //puts("233");
    }
    last = u;
    return u;
}

int conv(const char c) {
    if (c == 'N')
        return 0;
    else if (c == 'E')
        return 1;
    else if (c == 'W')
        return 2;
    else
        return 3;
}
int exec(char *p) {
    static Node *o;
    static int res, c;
    for (o = start, res = 0; *p; ++p, ++res) {
        c = conv(*p);
        if (o->ch[c])
            o = o->ch[c];
        else
            return res;
    }
    return res;
}

const int MAXS = 10000005, MAXT = 105;
int main() {
    static int n, m, i;
    static char s[MAXS], t[MAXT], *p;
    init(); // **
    scanf("%d%d", &n, &m);
    scanf("%s", s);
    for (p = s; *p; ++p)
        extend(conv(*p));
    for (i = 1; i <= m; ++i) {
        scanf("%s", t);
        printf("%d\n", exec(t));
    }

    return 0;
}
