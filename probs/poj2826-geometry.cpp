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
typedef long long ll;
typedef const int cint;
typedef const long long cll;
typedef const char cchar;
struct IO{static cint L=1000000;char a[L],b[L],*s,*t,*p,c;IO():p(b){}~IO(){fwrite(b,1,p-b,stdout);}char gc(){if(s==t)t=(s=a)+fread(a,1,L,stdin);return s==t?EOF:*s++;}void gs(char*st){for(c=gc();!isgraph(c);c=gc());*st++=c;for(c=gc();isgraph(c);c=gc())*st++=c;*st++=0;}template<class T>operator T(){static T x;static bool neg;for(c=gc();c!='-'&&!isdigit(c);c=gc());if((neg=c=='-'))c=gc();x=c-'0';for(c=gc();isdigit(c);c=gc())x=x*10+(c-'0');return neg?-x:x;}void pc(cchar ch){if(p==b+L)fwrite(p=b,1,L,stdout);*p++=ch;}template<class T>void print(T x,cchar end='\n'){static char cs[30],*q;static T y;if(x==0)pc('0');else{if(x<0)pc('-'),x=-x;for(q=cs;x;x=y)y=x/10,*q++=x-y*10+'0';while(q!=cs)pc(*--q);}if(end)pc(end);}void ps(cchar*st,cchar end='\n'){while(*st)pc(*st++);if(end)pc(end);}void pd(cint x){pc('0'+x);pc('\n');}}io;

const double eps = 1e-9;
int dcmp(const double x) {
    return fabs(x) <= eps ? 0 : (x > 0 ? 1 : -1);
}
int dcmp(const double x, const double y) {
    return dcmp(x - y);
}
struct point_t {
    double x, y;
    void rd() {
        x = (int)io;
        y = (int)io;
    }
    point_t() {}
    point_t(const double _a, const double _b) : x(_a), y(_b) {}
    point_t(const point_t &_a, const point_t &_b) : x(_b.x - _a.x), y(_b.y - _a.y) {}
    bool operator == (const point_t &rh) const {
        return dcmp(x, rh.x) == 0 && dcmp(y, rh.y) == 0;
    }
    double operator * (const point_t &rh) const {
        return x * rh.y - y * rh.x;
    }
    point_t operator + (const point_t &rh) const {
        return point_t(x + rh.x, y + rh.y);
    }
    point_t operator * (const double a) const {
        return point_t(x * a, y * a);
    }
    point_t operator / (const double a) const {
        return point_t(x / a, y / a);
    }
    bool on(const struct segment_t &l) const;
};
typedef point_t vector_t;
struct segment_t {
    point_t a, b;
    segment_t() {}
    segment_t(const point_t &_a, const point_t &_b) : a(_a), b(_b) {}
    void rd() {
        a.rd();
        b.rd();
    }
};
typedef segment_t line_t;
bool point_t::on(const segment_t &l) const {
    return dcmp(vector_t(l.a, *this) * vector_t(*this, l.b)) == 0 && dcmp((l.a.x - x) * (x - l.b.x)) >= 0;
}
bool is_proper_intersected(const segment_t &a, const segment_t &b) {
    return dcmp((vector_t(a.a, b.a) * vector_t(a.a, b.b)) * (vector_t(a.b, b.a) * vector_t(a.b, b.b))) < 0
        && dcmp((vector_t(b.a, a.a) * vector_t(b.a, a.b)) * (vector_t(b.b, a.a) * vector_t(b.b, a.b))) < 0;
}
bool is_intersected(const segment_t &a, const segment_t &b) {
    return (a.a == b.a) || (a.a == b.b) || (a.b == b.a) || (a.b == b.b) || is_proper_intersected(a, b);
}
point_t lines_intersect(const line_t &a, const line_t &b) {
    double s1 = vector_t(a.a, b.a) * vector_t(a.a, b.b), 
           s2 = vector_t(a.b, b.b) * vector_t(a.b, b.a);
    return a.a + vector_t(a.a, a.b) * s1 / (s1 + s2);
}
bool is_parallel(const line_t &a, const line_t &b) {
    return dcmp(vector_t(a.a, a.b) * vector_t(b.a, b.b)) == 0;
}
bool is_horizontal(const segment_t &a) {
    return dcmp(a.a.y, a.b.y) == 0;
}
double solve(segment_t a, segment_t b) {
    if (is_horizontal(a) || is_horizontal(b) || !is_intersected(a, b) || is_parallel(a, b))
        return 0;
    point_t p = lines_intersect(a, b), 
            ap = a.a.y > a.b.y ? a.a : a.b,
            bp = b.a.y > b.b.y ? b.a : b.b;
    if (ap.y > bp.y)
        std::swap(ap, bp), std::swap(a, b);
    if (dcmp(ap.x, bp.x) >= 0)
        return 0;
    point_t q = lines_intersect(line_t(ap, point_t(ap.x + 1, ap.y)), b);
    return fabs(vector_t(p, ap) * vector_t(p, q) / 2.0);
}
int main() {
    static int ks;
    static segment_t a, b;
    ks = io;
    while (ks--) {
        a.rd();
        b.rd();
        printf("%.2f\n", solve(a, b));
    }

    return 0;
}

