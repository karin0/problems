
#include <bits/stdc++.h>
#define rep(i_,s_,t_) for(int i_=(s_);i_<=(t_);++i_)
#define re(i_,s_,t_) for(int i_=(s_);i_<(t_);++i_)
#define per(i_,s_,t_) for(int i_=(s_);i_>=(t_);--i_)
#define pe(i_,s_,t_) for(int i_=(s_);i_>(t_);--i_)
#define koishi(e_,u_) for(Edge *e_=(u)_->e;e_;e_=e_->e)
#ifdef AKARI
    void c_() { std::cerr << "\033[39;0m" << std::endl; }
    template<typename T, typename... Args>
    void c_(T a, Args... args) { std::cerr << a << ", "; c_(args...); }
    #define ccc(args...) std::cerr << "\033[32;1m" << #args << "  =  ", c_(args)
    #define ccd(args...) std::cerr << "\033[32;1m", c_(args)
    #define ccf(args...) fprintf(stderr, args)
    #define drep(i_,s_,t_) for(int (i_)=(s_);(i_)<=(t_);++(i_))
#else
    #define ccc(...) 0
    #define ccd(...) 0
    #define ccf(...) 0
    #define drep(i_,s_,t_) if (false)
#endif
typedef long long ll;
typedef const int cint;
typedef const long long cll;
typedef const char cchar;
#define daze << '\n'

const int N = 0;
#define ok =='0'
#define fil(xxx) xxx=7
char a[200], b[200];
int main() {
    scanf("%s%s", a+1,b+1);
    int n=strlen(a+1), ans = 0;
    rep (i, 1, n) {
        if (a[i] ok &&b[i] ok) {
            bool flg = false;
            if (i > 1 && a[i - 1] ok)
                flg = 1, fil(a[i-1]);
            else if (i > 1 && b[i - 1] ok)
                flg = 1, fil(b[i-1]);
            else if (i < n  && a[i + 1] ok)
                flg = 1, fil(a[i+1]);
            else if (i < n  && b[i + 1] ok)
                flg = 1, fil(b[i+1]);
            if (flg)
                a[i] = b[i] = 7, ++ans;
        }
    }
    printf("%d\n", ans);

    return 0;
}


