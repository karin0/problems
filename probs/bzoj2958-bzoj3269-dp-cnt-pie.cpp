#include <bits/stdc++.h>
#define rep(def_i_,def_s_,def_t_) for((def_i_)=(def_s_);(def_i_)<=(def_t_);++(def_i_))
#define re(def_i_,def_s_,def_t_) for((def_i_)=(def_s_);(def_i_)<(def_t_);++(def_i_))
#define per(def_i_,def_s_,def_t_) for((def_i_)=(def_s_);(def_i_)>=(def_t_);--(def_i_))
#define pe(def_i_,def_s_,def_t_) for((def_i_)=(def_s_);(def_i_)>(def_t_);--(def_i_))
#define koishi(def_e_,def_u_) for(Edge *def_e_=def_u_->e;def_e_;def_e_=def_e_->e)
#ifdef AKARI
    void def_c_() { std::cerr << "\033[39;0m" << std::endl; }
    template<typename T, typename... Args>
    void def_c_(T a, Args... args) { std::cerr << a << ", "; def_c_(args...); }
    #define ccc(args...) std::cerr << "\033[32;1m" << #args << "  =  ", def_c_(args)
    #define ccf(args...) fprintf(stderr, args)
#else
    #define ccc(...) 0
    #define ccf(...) 0
#endif
typedef long long ll;
typedef const int cint;
typedef const long long cll;
typedef const char cchar;
struct IO{static cint L=1000000;char a[L],b[L],*s,*t,*z,c;IO():z(b){}~IO(){fwrite(b,1,z-b,stdout);}char gc(){if(s==t)t=(s=a)+fread(a,1,L,stdin);return s==t?EOF:*s++;}template<class T>operator T(){static T x;static bool f;for(c=gc();c!='-'&&!isdigit(c);c=gc());if((f=c=='-'))c=gc();x=c-'0';for(c=gc();isdigit(c);c=gc())x=x*10+(c-'0');return f?-x:x;}void gs(char*q){for(c=gc();!isgraph(c);c=gc());*q++=c;for(c=gc();isgraph(c);c=gc())*q++=c;*q++=0;}char gg(){for(c=gc();!isgraph(c);c=gc());return c;}void pc(cchar q){if(z==b+L)fwrite(z=b,1,L,stdout);*z++=q;}template<class T>void operator()(T x,cchar e='\n'){static char r[30],*q;static T y;if(x==0)pc('0');else{if(x<0)pc('-'),x=-x;for(q=r;x;x=y)y=x/10,*q++=x-y*10+'0';while(q!=r)pc(*--q);}if(e)pc(e);}void ps(cchar*q,cchar e='\n'){while(*q)pc(*q++);if(e)pc(e);}void pd(cint x){pc('0'+x);pc('\n');}}io;

const int N = 1000003, mo = 1000000007;
int n, k, f[N][3][2], s[2][N];
int ck(const int x) {
    return x >= mo ? x - mo : x;
}
void add(int &x, const int v) {
    x = ck(x + v);
}
void sub(int &x, const int v) {
    x = x < v ? x - v + mo : x - v;
}
int g(const int i, const int j) {
    return ck(f[i][j][0] + f[i][j][1]);
}
char a[N];
int main() {
    static int i, j, t;
    n = io; k = io;
    io.gs(a + 1);
    f[0][0][0] = 1;
    rep (i, 1, n) {
        s[0][i] = s[0][i - 1] + (a[i] == 'B');
        s[1][i] = s[1][i - 1] + (a[i] == 'W');
        if (a[i] != 'W') { // to fill with 'B'
            rep (j, 0, 2)
                f[i][j][0] = g(i - 1, j);
            if (i >= k && a[i - k] != 'B' && s[1][i - k] == s[1][i] && (t = i == k ? 1 : f[i - k][0][1])) { // notice when to exclude
                sub(f[i][0][0], t); // so should not use sum here
                add(f[i][1][0], t);
            }
        }
        if (a[i] != 'B') { // to fill with 'W'
            rep (j, 0, 2)
                f[i][j][1] = g(i - 1, j);
            if (i > k && a[i - k] != 'W' && s[0][i - k] == s[0][i] && (t = f[i - k][1][0])) {
                sub(f[i][1][1], t);
                add(f[i][2][1], t);
            }
        }
    }
    io(g(n, 2));

    return 0;
}
