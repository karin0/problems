#include <cstdio>
#include <cctype>
#include <queue>
#include <algorithm>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))

struct IO {
    static const int L = 1000000;
    char a[L], b[L], *s, *t, *p;
    IO() : p(b) {}
    inline char gc() {
        if (s == t)
            t = (s = a) + fread(a, 1, L, stdin);
        return *s++; // return s == t ? -1 : *s++;
    }
    template <class T>
    operator T() {
        static T x;
        static char c;
        static bool neg;
        for (c = gc(); c != '-' && !isdigit(c); c = gc());
        if (c == '-')
            neg = true, c = gc();
        else
            neg = false;
        x = c - '0';
        for (c = gc(); isdigit(c); c = gc())
            x = x * 10 + (c - '0');
        return neg ? -x : x;
    }
    inline void pc(const char c) {
        if (p == b + L)
            fwrite(b, 1, L, stdout), p = b;
        *p++ = c;
    }
    template<class T>
    void print(T x, const bool nl = true) {
        static char c[30], *q;
        static T y;
        if (x == 0)
            pc('0');
        else {
            if (x < 0)
                pc('-'), x = -x;
            for (q = c; x; x = y)
                y = x / 10, *q++ = x - y * 10 + '0';
            while (q != c)
                pc(*--q);
        }
        if (nl)
            pc('\n');
    }
    inline void flush() const {
        fwrite(b, 1, p - b, stdout); // p = b;
    }
} io;
const int N = 20005, Q = 100005, inf = 0x3f3f3f3f;
int n, m, vx[N], vy[N], d[N], xb0, xb1, yb0, yb1, dy, aid;
struct Pos {
    int x, y;
    Pos() {}
    Pos(const int _x, const int _y) : x(_x), y(_y) {}
};
inline int id(const int x, const int y) {
    return (x - 1) * m + y;
}
inline int id(const Pos &u) {
    return (u.x - 1) * m + u.y;
}
inline void upd(int &x, const int v) {
    x = std::min(x, v);
}
struct Query {
    Pos u, v;
    int uid, vid, *ans;
} qwq[Q];
struct Data {
    Pos u;
    int uid, dis;
    Data() {}
    Data(const Pos &_u, const int _uid, const int _d) : u(_u), uid(_uid), dis(_d) {}
    bool operator < (const Data &rhs) const {
        return dis > rhs.dis;
    }
};
bool fir = true;
void dijkstra(const Pos &s, const int sid) {
    static std::priority_queue<Data> pq; 
    static int x, uid, vid, t, du, q;
    static Pos u;
    static Data dt;
    uid = aid;
    if (fir) {
        for (x = xb0; x <= xb1; ++x, uid = t + m)
            for (q = dy + (t = uid); uid <= q; ++uid)
                d[uid] = inf;
        fir = false;
    } else {
        du = d[sid];
        for (x = xb0; x <= xb1; ++x, uid = t + m)
            for (q = dy + (t = uid); uid <= q; ++uid)
                d[uid] += du;
    }
    d[sid] = 0;
    pq.push(Data(s, sid, 0));
    while (!pq.empty()) {
        dt = pq.top();
        pq.pop();
        u = dt.u, uid = dt.uid, du = d[uid];
        if (u.x > xb0) {
            vid = uid - m;
            t = du + vx[vid];
            if (d[vid] > t)
                pq.push(Data(Pos(u.x - 1, u.y), vid, d[vid] = t));
        }
        if (u.x < xb1) {
            vid = uid + m;
            t = du + vx[uid];
            if (d[vid] > t)
                pq.push(Data(Pos(u.x + 1, u.y), vid, d[vid] = t));
        }
        if (u.y > yb0) {
            vid = uid - 1;
            t = du + vy[vid];
            if (d[vid] > t)
                pq.push(Data(Pos(u.x, u.y - 1), vid, d[vid] = t));
        }
        if (u.y < yb1) {
            vid = uid + 1;
            t = du + vy[uid];
            if (d[vid] > t)
                pq.push(Data(Pos(u.x, u.y + 1), vid, d[vid] = t));
        }
    }
}
void solve(const Pos a, const Pos b, Query *const ql, Query *const qr) {
    if (ql > qr || a.x > b.x || a.y > b.y)
        return;
    xb0 = a.x, xb1 = b.x, yb0 = a.y, yb1 = b.y;
    aid = id(a);
    dy = yb1 - yb0;
    Query *tl = ql, *tr = qr, *q;
    if (xb1 - xb0 > yb1 - yb0) {
        int mid = (xb0 + xb1) >> 1, uid;
        Pos u = Pos(mid, yb0);
        for (uid = id(u); u.y <= yb1; ++u.y, ++uid) {
            dijkstra(u, uid);
            for (q = ql; q <= qr; ++q)
                upd(*q->ans, d[q->uid] + d[q->vid]);
        }
        for (q = ql; q <= tr; ++q) 
            if (q->u.x < mid && q->v.x < mid)
                *tl++ = *q;
            else if (q->u.x > mid && q->v.x > mid)
                std::swap(*tr--, *q--);
        }
        solve(a, Pos(mid - 1, b.y), ql, tl - 1);
        solve(Pos(mid + 1, a.y), b, tr + 1, qr);
    } else {
        int mid = (yb0 + yb1) >> 1, uid;
        Pos u = Pos(xb0, mid);
        for (uid = id(u); u.x <= xb1; ++u.x, uid += m) {
            dijkstra(u, uid);
            for (q = ql; q <= qr; ++q)
                upd(*q->ans, d[q->uid] + d[q->vid]);
        }
        for (q = ql; q <= tr; ++q) {
            if (q->u.y < mid && q->v.y < mid)
                *tl++ = *q;
            else if (q->u.y > mid && q->v.y > mid)
                std::swap(*tr--, *q--);
        }
        solve(a, Pos(b.x, mid - 1), ql, tl - 1);
        solve(Pos(a.x, mid + 1), b, tr + 1, qr);
    }
}

int main() {
    static int i, j, p, c, ans[Q];
    n = io, m = io;
    c = 0;
    rep (i, 1, n) {
        re (j, 1, m)
            vy[++c] = io;
        ++c;
    }
    c = 0;
    re (i, 1, n) rep (j, 1, m)
        vx[++c] = io;
    p = io;
    rep (i, 1, p) {
        Query &q = qwq[i];
        q.u.x = io, q.u.y = io, q.v.x = io, q.v.y = io;
        q.uid = id(q.u), q.vid = id(q.v);
        q.ans = &ans[i];
        ans[i] = inf;
    }
    solve(Pos(1, 1), Pos(n, m), qwq + 1, qwq + p);
    rep (i, 1, p)
        io.print(ans[i]);

    io.flush(); // ***
    return 0;
}
