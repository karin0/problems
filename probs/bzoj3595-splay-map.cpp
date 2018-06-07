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
    #define ccc(x) 0
    #define ccf(x) 0
    #define cccc(...) 0
#endif
struct IO{static const int L=1000000;char a[L],b[L],*s,*t,*p,c;IO():p(b){}~IO(){fwrite(b,1,p-b,stdout);/*p=b;*/}char gc(){if(s==t)t=(s=a)+fread(a,1,L,stdin);return*s++;/*return s==t?EOF:*s++;*/}void gs(char*st){for(c=gc();!isgraph(c);c=gc());*st++=c;for(c=gc();isgraph(c);c=gc())*st++=c;*st++=0;}template<class T>operator T(){static T x;static bool neg;for(c=gc();c!='-'&&!isdigit(c);c=gc());if((neg=c=='-'))c=gc();x=c-'0';for(c=gc();isdigit(c);c=gc())x=x*10+(c-'0');return neg?-x:x;}void pc(const char ch){if(p==b+L)fwrite(p=b,1,L,stdout);*p++=ch;}template<class T>void print(T x,const char end='\n'){static char cs[30],*q;static T y;if(x==0)pc('0');else{if(x<0)pc('-'),x=-x;for(q=cs;x;x=y)y=x/10,*q++=x-y*10+'0';while(q!=cs)pc(*--q);}if(end)pc(end);}void ps(const char*st,const char end='\n'){while(*st)pc(*st++);if(end)pc(end);}}io;
typedef long long ll;

struct Node *rt;
struct Node {
    Node *ch[2], *fa;
    int x, len, siz;
    Node(const int _x, const int _l, Node *_f) : fa(_f), x(_x), len(_l), siz(_l) {}
    static void link(Node *o, Node *f, const int r) {
        if (o)
            o->fa = f;
        if (f)
            f->ch[r] = o;
    }
    void maintain() {
        siz = len + (ch[0] ? ch[0]->siz : 0) + (ch[1] ? ch[1]->siz : 0);
    }
    int rel() {
        return fa && this == fa->ch[1];
    }
    void rotate() {
        static Node *f;
        static int r;
        f = fa;
        r = rel();
        link(this, f->fa, f->rel());
        link(ch[r ^ 1], f, r);
        link(f, this, r ^ 1);
        f->maintain();
        maintain();
        if (fa == NULL)
            rt = this;
    }
    void splay(Node *des = NULL) {
        while (fa != des) {
            if (fa->fa == des)
                return rotate();
            else if (rel() == fa->rel())
                fa->rotate(), rotate();
            else
                rotate(), rotate();
        }
    }
    int rk() {
        return ch[0] ? ch[0]->siz : 0;
    }
    Node *succ() {
        Node *o = ch[1];
        for (; o->ch[0]; o = o->ch[0]);
        return o;
    }
    Node *prev() {
        Node *o = ch[0];
        for (; o->ch[1]; o = o->ch[1]);
        return o;
    }
    void cut() {
        splay();
        if (ch[1]) {
            Node *o = succ();
            o->splay(this);
            link(ch[0], o, 0);
            rt = o;
        } else
            rt = ch[0];
        rt->fa = NULL;
        rt->maintain();
        ch[0] = ch[1] = NULL;
    }
    Node *split(const int rx) {
        // ccc(x); ccc(len); ccf(rx);
        splay();
        Node *p;
        if (ch[1]) {
            Node *o = succ();
            o->splay(this);
            o->ch[0] = p = new Node(rx, len - (rx - x), o);
            o->maintain();
        } else
            ch[1] = p = new Node(rx, len - (rx - x), this);
        len = rx - x;
        maintain();
        return p;
    }
};
std::map<int, Node *> mp;
void link(Node *o, Node *f, const int r) {
    if (o)
        o->fa = f;
    if (f)
        f->ch[r] = o;
}
Node *select2(const int r) {
    Node *o = rt;
    for (; o->ch[r]; o = o->ch[r]);
    return o->splay(), o;
}
Node *split_out(const int x) {
    static Node *o;
    static std::map<int, Node *>::iterator it;
    it = mp.lower_bound(x);
    if (it == mp.end() || it->first != x) {
        --it;
        o = it->second->split(x);
        mp[x] = o;
    } else
        o = it->second;
    if (o->x + o->len >= x + 2)
        mp[x + 1] = o->split(x + 1);
    return o;
}
Node *split_out_and_erase(const int x) {
    static Node *o;
    static std::map<int, Node *>::iterator it;
    it = mp.lower_bound(x);
    if (it == mp.end() || it->first != x) {
        --it;
        o = it->second->split(x);
    } else {
        o = it->second;
        mp.erase(x);
    }
    if (o->x + o->len >= x + 2)
        mp[x + 1] = o->split(x + 1);
    return o;
}
int change(const int x, const int y) {
    // printf("change %d to %d\n",x,y);
    Node *o = split_out_and_erase(x);
    // assert(o->len == 1);
    o->x = y;
    mp[y] = o;
    o->splay();
    return o->rk() + 1;
}
int move_to(const int x, const int r) {
    Node *o = split_out(x);
    // assert(o->len == 1);
    o->splay();
    int res = o->rk() + 1;
    o->cut();
    link(select2(r), o, r ^ 1);
    rt = o;
    rt->maintain();
    return res;
}
int query_at(int x) {
    static int ork;
    static Node *o;
    --x;
    o = rt;
    while (true) {
        ork = o->rk();
        if (ork > x)
            o = o->ch[0];
        else if (ork + o->len <= x)
            x -= ork + o->len, o = o->ch[1]; // ccf("right");
        else
            return o->x + x - ork;
    }
}
/* void print(Node *o) {
    if (o->ch[0])
        print(o->ch[0]);
    printf(" %d~%d", o->x, o->x + o->len - 1);
    if (o->ch[1])
        print(o->ch[1]);
} */

int main() {
    static int m, x, op, la, t;
    mp[1] = rt = new Node(1, io, NULL);
    m = io;
    while (m--) {
        /* ccc(rt->x); ccc(rt->len); ccc(rt->siz); ccf(rt->rk());
        print(rt);
        puts(""); */
        op = io;
        x = (int)io - la;
        // printf("doing %d %d\n", op, x);
        switch (op) {
            case 1:  t = la; la = change(x, (int)io - t); break;
            case 2:  la = move_to(x, 0); break;
            case 3:  la = move_to(x, 1); break;
            default: la = query_at(x);
        }
        // io.print(la);
        printf("%d\n", la);
    }

    return 0;
}
