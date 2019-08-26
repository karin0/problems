    sort(use,use+n,cmp);

    for(int i=0,j=1%n;i<n;++i){

        while(j!=i and (use[i]^use[j])>=0)

            j=(j+1)%n;

    }
struct node{

    ll x,y;

    int xx;

    node(){}

    node(ll _x,ll _y){

        x=_x,y=_y;

        if(y==0){

            if(x>=0)xx=1;

            else xx=2;

        }else{

            if(y>0)xx=1;

            else xx=2;

        }

    }

    node operator-(const node&p)const{

        return node(x-p.x,y-p.y);

    }

    ll operator^(const node&p)const{

        return x*p.y-y*p.x;

    }

    ll operator*(const node&p)const{

        return x*p.x + y*p.y;

    }

};

bool cmp(const node&le,const node&ri){

    if(le.xx==ri.xx)return (le^ri)>0;

    else return le.xx<ri.xx;

}


#include <cstdio>
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)
typedef long long ll;

#ifdef AKARI
void cca() {
    std::cerr << "\033[39;0m" << std::endl;
}
template <typename T, typename... Args>
void cca(T a, Args... args) {
    std::cerr << a << ", ";
    cca(args...);
}
    #define ccc(args...) std::cerr << "\033[32;1m" << #args << "  =  ", cca(args)
    #define ccf(args...) fprintf(stderr, args)
    #define crep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#else
    #define ccc(...) 0
    #define ccf(...) 0
    #define crep(...) if (0)
#endif


cint N = 50002;

struct Pt {
    double x, y;
    Pt() {}
    Pt(const double x, const double y) : x(x), y(y) {}
    void read() {
        int a, b;
        scanf("%d%d", &a, &b);
        x = a, y = b;
    }
    Pt operator - () const {
        return Pt(-x, -y);
    }
    Pt operator - (const Pt &rhs) const {
        return Pt(x - rhs.x, y - rhs.y);
    }
    Pt operator + (const Pt &rhs) const {
        return Pt(x + rhs.x, y + rhs.y);
    }
    Pt operator * (const double k) const {
        return Pt(x * k, y * k);
    }
    Pt &operator *= (const double k) {
        return *this = *this * k;
    }
    double operator * (const Pt rhs) const {
        return x * rhs.y - y * rhs.x;
    }
    double norm2() const {
        return x * x + y * y;
    }
    double norm() const {
        return sqrt(norm2());
    }
    Pt normal() const {
        return Pt(y, -x);
    }
} pts[N];

struct Func {
    double a, b, c;
    Func(const Pt &p, const Pt &q) : a(p.y - q.y), b(q.x - p.x), c(p * q) {}
    double operator () (const Pt &p) const {
        return fabs(a * p.x + b * p.y + c);
    }
};

/*
void say(double x, const char end) {
    if (x < 0) {
        io << '-';
        x = -x;
    }
    int i = x, j = round((x - i) * 10000000);
    io << i << '.';
    if (j)
        io << j;
    else
        io << "0000000";
    io << end;
}
*/

inline Pt intersect(const Pt &aa, const Pt &ab, const Pt &ba, const Pt &bb) {
    double s1 = (ba - aa) * (bb - aa), s2 = (bb - ab) * (ba - ab);
    return aa + (ab - aa) * (s1 / (s1 + s2));
}

int main() {
#ifndef AKARI
    freopen("flags.in", "r", stdin);
#endif

    int T;
    scanf("%d", &T);
    rep (ks, 1, T) {
        printf("Case %d:\n", ks);
        int n, m;
        scanf("%d", &n);
        rep (i, 1, n)
            pts[i].read();
        scanf("%d", &m);
        while (m--) {
            Pt p1, p2;
            p1.read();
            p2.read();

            double ans = DBL_MAX;
            Pt ans2;
            rep (i, 1, n) {
                const Pt &a = pts[i], &b = pts[i < n ? i + 1 : 1];
                const Func f(a, b);
                double d = f(p1) / sqrt(f.a * f.a + f.b * f.b);
                const Pt t = a - b;
                Pt v = t.normal() * (d / t.norm()), v2 = -v;
                Pt o = p1 + v, o2 = p1 + v2;
                o = f(o) > f(o2) ? o2 + v2 : o + v;
                double dis = (o - p2).norm2();
                if (dis < ans) {
                    Pt u = intersect(p2, o, a, b);
                    double x1, x2, y1, y2;
                    std::tie(x1, x2) = std::minmax(a.x, b.x);
                    std::tie(y1, y2) = std::minmax(a.y, b.y);
                    if (x1 <= u.x && u.x <= x2 && y1 <= u.y && u.y <= y2)
                        ans = dis, ans2 = u;
                }
            }
            printf("%.7f %.7f %.7f\n", sqrt(ans), ans2.x , ans2.y);
        }
    }
    
    return 0;
}
