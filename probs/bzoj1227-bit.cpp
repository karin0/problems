#include <cstdio>
#include <cctype>
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
    void gs(char *st) {
        static char c;
        for (c = gc(); !isgraph(c); c = gc());
        *st++ = c;
        for (c = gc(); isgraph(c); c = gc())
            *st++ = c;
        *st++ = 0;
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
    void ps(const char *st, const bool nl = true) {
        while (*st)
            pc(*st++);
        if (nl)
            pc('\n');
    }
    inline void flush() const {
        fwrite(b, 1, p - b, stdout); // p = b;
    }
} io;

const int N = 100003;
int xcnt = 1, c[N];
struct Item {
    int x, y, xi, yi;
} qwq[N];
bool cmp_x(const Item &u, const Item &v) {
    return u.x < v.x || (u.x == v.x && u.y < v.y);
}
bool cmp_y(const Item &u, const Item &v) {
    return u.y < v.y || (u.y == v.y && u.x < v.x);
}
int main() {
    static int w, k, i, j, t, p, b, z, x, toty, cx[N], cy[N], l, r, ycnt = 1, comb[N][12], ans, cc[N];
    w = io;
    w = io;
    w = io;
    re (i, 0, w) {
        Item &q = qwq[i];
        q.x = io, q.y = io;
    }
    k = io;
    std::sort(qwq, qwq + w, cmp_x);
    qwq[0].xi = 1;
    re (i, 1, w) {
        Item &q = qwq[i];
        if (q.x == qwq[i - 1].x)
            q.xi = xcnt;
        else
            q.xi = ++xcnt;
    }
    std::sort(qwq, qwq + w, cmp_y);
    qwq[0].yi = 1;
    re (i, 1, w) {
        Item &q = qwq[i];
        if (q.y == qwq[i - 1].y)
            q.yi = ycnt;
        else
            q.yi = ++ycnt;
    }
    re (i, 0, w) {
        Item &q = qwq[i];
        q.x = q.xi;
        q.y = q.yi;
        ++cx[q.x];
        ++cy[q.y];
        //  printf("#%d x = %d, y = %d\n", i, q.x, q.y);
    }
    comb[0][0] = comb[1][0] = comb[1][1] = 1;
    rep (i, 2, w) {
        comb[i][0] = 1;
        t = std::min(i, k);
        rep (j, 1, t)
            comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
    }
    rep (i, 0, w)
        cc[i] = comb[i][k];
    // rep (i, 0, w) rep (j, 0, k) printf("c[%d][%d] = %d\n",i,j,comb[i][j]);
    l = 0;
    ++c[qwq[0].x];
    re (i, 1, w) {
        Item &q = qwq[i];
        if (q.y + k - 1 > ycnt)
            break;
        if (q.y != qwq[i - 1].y) {
            // printf("l = %d\n", l);
            toty = qwq[i - 1].y;
            for (j = l + k - 1; ; ++j) {
                // printf("!!!!j = %d, toty = %d, cy = %d, j-l+1 = %d\n", j,toty,cy[toty],j-l+1);
                z = j - l + 1;
                p = cy[toty] - z;
                if (p < k)
                    break;
                // puts("pass");
                for (x = qwq[j].x + 1; x < qwq[j + 1].x; ++x) {
                    t = c[x];
                    // printf("i, j, x,  t, cx = %d, %d, %d, %d, %d\n", i, j, x, t, cx[x]);
                    b = cx[x] - t;
                    if (t >= k && b >= k)
                        ans += cc[z] * cc[p] * cc[t] * cc[b];
                }
            }
            l = i;
        }
        ++c[q.x];
    }

    io.print(ans & 0x7fffffff);
    io.flush(); // ***
    return 0;
}
