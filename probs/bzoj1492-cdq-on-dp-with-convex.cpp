#include <bits/stdc++.h>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))
#ifdef AKARI
    #define SAY(x) std::cerr << #x " = " << x << std::endl
#else
    #define SAY(x) 0
#endif

const int N = 100003;
const double eps = 1e-9, inf = 1e20;
int dcmp(const double x) {
    return fabs(x) <= eps ? 0 : (x > 0 ? 1 : -1);
}
struct Vec {
    double x, y;
    Vec() {}
    Vec(double _x, double _y) : x(_x), y(_y) {}
    Vec(const Vec &p, const Vec &q) : x(q.x - p.x), y(q.y - p.y) {}
} co[N], t1[N];
struct Data {
    double a, b, k, r, *f;
    Vec p;
} a[N], t2[N], qw[N];
double cross(const Vec &p, const Vec &q) {
    return p.x * q.y - p.y * q.x;
}
bool cmp1(const Vec &p, const Vec &q) {
    static int t;
    t = dcmp(p.x - q.x);
    return t < 0 || (t == 0 && dcmp(p.y - q.y) < 0);
}
bool cmp2(const Data &p, const Data &q) {
    return p.k > q.k;  // ******************* damn it
}
double f[N];
void cdq(const int l, const int r) {
    if (l == r) {
        Data &q = a[l];
        *q.f = std::max(*q.f, *a[l - 1].f);
        double t = q.a * q.r + q.b;
        q.p = Vec(*q.f * q.r / t, *q.f / t);
        return;
    }
    int mid = (l + r) >> 1, i, c1 = 0, c2 = 0, cnt = 0, cur = 1; // cw = 0;
    cdq(l, mid);
    rep (i, l, mid)
        t1[++c1] = a[i].p;
    rep (i, mid + 1, r)
        t2[++c2] = a[i];
    std::sort(t1 + 1, t1 + c1 + 1, cmp1);
    std::sort(t2 + 1, t2 + c2 + 1, cmp2);
    rep (i, 1, c1) {
        Vec &q = t1[i];
        while (cnt >= 2 && dcmp(cross(Vec(co[cnt - 1], co[cnt]), Vec(co[cnt - 1], q))) >= 0)  // ******
            --cnt;
        co[++cnt] = q;
    }
    // double k, kn;
    rep (i, 1, c2) {
        Data &q = t2[i];
        while (cur < cnt && (dcmp(cross(Vec(co[cur], co[cur + 1]), Vec(-q.b, q.a))) > 0))  // ??????? ******
            ++cur;
        *q.f = std::max(*q.f, q.a * co[cur].x + q.b * co[cur].y);
    }
    /*
    for (i = 1; i <= cnt; ++i, kp = kn) {
        Vec &p = co[i];
        kn = i == cnt ? -inf : slope(p, co[i + 1]);
        SAY(l);
        SAY(r);
        SAY(kn);
        if (dcmp(kn - kp) == 0)
            continue;
        while (cw) {
            Data &q = qw[cw--];
            *q.f = std::max(*q.f, q.a * p.x + q.b * p.y);
        }
        while (cur <= c2 && (k = t2[cur].k, dcmp(kp - k) >= 0 && dcmp(k - kn) >= 0)) {
            Data &q = t2[cur++];
            //printf("Upd %ld\n", q.f-f);
            *q.f = std::max(*q.f, q.a * p.x + q.b * p.y);
            if (dcmp(q.k - kn) == 0)
                qw[++cw] = q;
        }
    }*/
    cdq(mid + 1, r);
}
int main() {
    static int n, i;
    scanf("%d%lf", &n, &f[1]);
    a[0].f = &f[0];
    rep (i, 1, n) {
        Data &q = a[i];
        scanf("%lf%lf%lf", &q.a, &q.b, &q.r);
        q.k = -q.a / q.b;
        q.f = &f[i];
    }
    cdq(1, n);
    printf("%.3f\n", f[n]);

    return 0;
}
