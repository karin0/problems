#include <cstdio>
#include <cmath>
#include <algorithm>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)
typedef long long ll;

const int N = 200002;
// const double eps = 1e-7;

int mx;
ll rrs;
int rrc;
struct SegT *nil;
struct SegT {
    SegT *lc, *rc;
    int cnt;
    ll sum;
    SegT() {}
    SegT(SegT *_l, SegT *_r) : lc(_l), rc(_r), cnt(lc->cnt + rc->cnt), sum(lc->sum + rc->sum) {}
    SegT(const SegT *o, ll s) : lc(nil), rc(nil), cnt(o->cnt + 1), sum(o->sum + s) {}
    SegT *insert(const int i, const int l = 1, const int r = mx) const {
        if (l == r)
            return new SegT(this, i);
        int mid = (l + r) >> 1;
        if (i <= mid)
            return new SegT(lc->insert(i, l, mid), rc);
        else
            return new SegT(lc, rc->insert(i, mid + 1, r));
    }
    void *operator new (size_t) {
        static SegT pool[N * 18], *curr = pool;
        return curr++;
    }
    void qsum(const int ql, const int qr, const int l = 1, const int r = mx) const {
        if (ql <= l && r <= qr) {
            //printf("ql=%d, qr=%d, l=%d, r=%d, sum=%lld, cnt=%d\n",ql,qr,l,r,sum,cnt);
            rrc += cnt;
            rrs += sum;
            return;
        }
        int mid = (l + r) >> 1;
        if (ql <= mid)
            lc->qsum(ql, qr, l, mid);
        if (qr > mid)
            rc->qsum(ql, qr, mid + 1, r);
    }
} *segt[N];

/*
ll query(ll k, SegT *tl, SegT *tr) {
    ll lb = 1, rb = mx;
    while (lb < rb) {
        ll s = tr->cnt - tl->cnt;
        if (k <= s)
            tl = tl->lc, tr = tr->rc;
        else
            tl = tl->rc, tr = tr->rc;
    }
}*/

int a[N];
ll s[N];
int main() {
    segt[0] = nil = new SegT;
    nil->lc = nil->rc = nil;
    int n, m;
    scanf("%d%d", &n, &m);
    rep (i, 1, n) {
        scanf("%d", &a[i]);
        mx = std::max(mx, a[i]);
        s[i] = s[i - 1] + a[i];
    }
    rep (i, 1, n)
        segt[i] = segt[i - 1]->insert(a[i]);

   // printf("mx = %d\n", mx);
    while (m--) {
        int l, r, x, y;
        scanf("%d%d%d%d", &l, &r, &x, &y);
        long double t = (long double)(s[r] - s[l - 1]) * x / y, al = 0, ar = mx, amid;
        //printf("t = %f\n", (double)t);
        int lll = 50, ltm = -1, ltc;
        ll lts;
        while (lll--) {
            //printf("(%f, %f)\n", (double)al, (double)ar);
            amid = (al + ar) / 2.0;

            int tm = ceil(amid);

            if (tm != ltm) {
                ltm = tm;
                rrc = rrs = 0;
                segt[r]->qsum(tm, mx);
                ltc = rrc;
                lts = rrs;
                rrc = rrs = 0;
                segt[l - 1]->qsum(tm, mx);
                ltc -= rrc;
                lts -= rrs;
            }

            long double sss = lts - ltc * amid;
           // printf("(%f, %f), mid=%f, truemid=%d, tc=%d, ts=%lld, sss = %f\n", (double)al, (double)ar, (double)amid, tm, ltc,lts,(double)sss);
            // printf("ts = %f\n", ts);
            if (sss < t)
                ar = amid;
            else if (sss > t)
                al = amid;
            else
                break;
        }
        printf("%.15f\n", (double)amid);
    }
}