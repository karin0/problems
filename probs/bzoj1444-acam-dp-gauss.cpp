#include <bits/stdc++.h>
#define rep(i_,s_,t_) for(int i_=(s_);i_<=(t_);++i_)
#define re(i_,s_,t_) for(int i_=(s_);i_<(t_);++i_)
#define per(i_,s_,t_) for(int i_=(s_);i_>=(t_);--i_)
#define pe(i_,s_,t_) for(int i_=(s_);i_>(t_);--i_)
#define go(e_,s_) for(Edge *e_=(s_);e_;e_=e_->e)
#ifdef AKARI
    void c_() { std::cerr << "\033[39;0m" << std::endl; }
    template<typename T, typename... Args>
    void c_(T a, Args... args) { std::cerr << a << ", "; c_(args...); }
    #define ccc(args...) std::cerr << "\033[32;1m" << #args << "  =  ", c_(args)
    #define ccd(args...) std::cerr << "\033[32;1m", c_(args)
    #define ccf(args...) fprintf(stderr, args)
    #define crep(i_,s_,t_) for(int i_=(s_);i_<=(t_);++i_)
#else
    #define ccc(...) 0
    #define ccd(...) 0
    #define ccf(...) 0
    #define crep(...) if (false)
#endif
typedef long long ll;
typedef const int cint;
typedef const long long cll;
typedef const char cchar;
#define oper operator
#define daze << '\n'
cint p_[]={10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};template<cint LI,cint LO>struct IO{char a[LI],b[LO],r[20],*s,*t,*z,c;IO():z(b){}~IO(){if(z!=b)fwrite(b,1,z-b,stdout);}char gc(){if(s==t)t=(s=a)+fread(a,1,LI,stdin);return s==t?EOF:*s++;}template<class T>IO&oper>>(T&x){for(c=gc();c!='-'&&!isdigit(c);c=gc());bool f=c=='-';if(f)c=gc();x=c-'0';for(c=gc();isdigit(c);c=gc())x=x*10+(c-'0');if(f)x=-x;return*this;}IO&oper>>(char*x){for(c=gc();!isgraph(c);c=gc());*x++=c;for(c=gc();isgraph(c);*x++=c,c=gc());*x=0;return*this;}IO&oper>>(char&x){for(x=gc();!isgraph(x);x=gc());return*this;}IO&oper>>(double&x){int p,y;*this>>p;if(c=='.'){*this>>y;for(x=y;x>1;x/=10);if(p<0)x=p-x;else x+=p;}else x=p;return*this;}template<class T>oper T(){T x;*this>>x;return x;}void pc(cchar x){if(z==b+LO)fwrite(z=b,1,LO,stdout);*z++=x;}void fl(){fwrite(b,1,z-b,stdout);z=b;}template<class T>struct d{T x;int l;d(const T x_,cint l_):x(x_),l(l_){}oper T&(){return x;}};template<class T>d<T>operator()(const T x,cint l){return d<T>(x,l);}template<class T>IO&oper<<(T x){if(x==0)pc('0');else{if(x<0)pc('-'),x=-x;T y;char*j=r;for(;x;x=y)y=x/10,*j++=x-y*10+'0';while(j!=r)pc(*--j);}return*this;}template<class T>IO&oper<<(d<T>x){if(x==0)re(i,0,x.l)pc('0');else{if(x<0)pc('-'),x.x=-x;T y;char*j=r;for(;x;x.x=y,--x.l)y=x/10,*j++=x-y*10+'0';for(;x.l;pc('0'),--x.l);while(j!=r)pc(*--j);}return*this;}IO&oper<<(d<double>x){if(x<0)pc('-'),x.x=-x;int w=floor(x);*this<<w;pc('.');int e=(x-w)*p_[x.l],u=e/10;if(e-u*10>=5)++u;return*this<<d<int>(u,x.l);}IO&oper<<(const double x){return*this<<d<double>(x,6);}IO&oper<<(char*x){while(*x)pc(*x++);return*this;}IO&oper<<(cchar*x){while(*x)pc(*x++);return*this;}IO&oper<<(cchar x){return pc(x),*this;}template<class T>void oper()(T x){*this<<x;}};
IO<1000000, 1000000> io;
cint N = 12, R = N * N * 2;

double a[R][R];
void gauss(cint n) {
    re (i, 0, n) {
        int p = i;
        re (j, i + 1, n) if (fabs(a[j][i]) > fabs(a[p][i]))
            p = j;
        if (p != i) rep (j, i, n)
            std::swap(a[i][j], a[p][j]);
        re (j, 0, n) if (i != j) {
            double t = a[j][i] / a[i][i];
            per (k, n, i)
                a[j][k] -= a[i][k] * t;
        }
    }
}
int m, ncnt;
struct Node {
    Node *ch[N], *fail;
    bool w;
} *rt, pool[R], *curr = pool;
Node *insert(cchar *s) {
    Node *u = rt;
    for (; *s; ++s) {
        Node *&v = u->ch[*s - 'A'];
        if (!v) v = new (curr++) Node;
        u = v;
    }
    u->w = true;
    return u;
}
void build() {
    static std::queue<Node *> q;
    rt->fail = rt;
    re (i, 0, m) {
        Node *&v = rt->ch[i];
        if (v) {
            v->fail = rt;
            q.push(v);
        } else
            v = rt;
    }
    while (!q.empty()) {
        Node *u = q.front();
        q.pop();
        re (i, 0, m) {
            Node *&v = u->ch[i];
            if (v) {
                v->fail = u->fail->ch[i];
                q.push(v);
            } else
                v = u->fail->ch[i];
        }
    }
}
int n, l, w[N];
char s[N][N];
double p[N];
bool impossible[N];
int main() {
    rt = new (curr++) Node;
    io >> n >> l >> m;
    re (i, 0, m) {
        int x(io);
        if (x == 0) impossible[i] = true, x = io;
        else p[i] = (double)x / (int)io;
        // ccc(i, p[i]);
    }
    int icnt = 0;
    re (i, 0, n) {
        io >> s[i];
        bool imp = false;
        for (char *c = s[i]; *c; ++c) if (impossible[*c - 'A']) { // ****
            imp = true;
            break;
        }
        if (imp) ++icnt, w[i] = -1;
        else w[i] = insert(s[i]) - pool;
        // ccc(i, s[i]);
    }
    if (icnt == n) {
        re (i, 0, n)
            // io << "0.00\n";
            puts("0.00");
        return 0;
    }
    build();
    ncnt = curr - pool;
    for (Node *u = pool; u < curr; ++u) {
        a[u - pool][u - pool] = -1;
        if (!u->w) re (i, 0, m)
            a[u->ch[i] - pool][u - pool] += p[i]; // *
    }
    a[0][ncnt] = -1;
    gauss(ncnt);
    re (i, 0, n) {
        if (w[i] == -1) /*io << "0.00\n";*/ puts("0.00");
        else {
            double x = a[w[i]][ncnt] / a[w[i]][w[i]];
            if (fabs(a[w[i]][w[i]]) < 1e-8 || x != x || fabs(x) < 1e-4)  puts("0.00"); //io << "0.00\n";
            else printf("%.2f\n", x); // io << io(x, 2) daze;
        // printf("%.2f\n", a[w[i]][ncnt] / a[w[i]][w[i]]);
        }
    }
}
