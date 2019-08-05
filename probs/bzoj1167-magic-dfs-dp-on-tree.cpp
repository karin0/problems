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
 
typedef long long ll;
const int N = 300003, inf = 1023333333;
int n, w[N];
struct Data {
    int val, succ;
    Data() {}
    Data(const int _v, const int _s) : val(_v), succ(_s) {}
    bool operator < (const Data &rhs) const {
        return !(*this > rhs);
    }
    bool operator > (const Data &rhs) const {
        return val > rhs.val || (val == rhs.val && succ < rhs.succ);
    }
} d1[N], d2[N], d3[N];
const Data DATA_MIN = Data(-inf, inf);
struct vector_int {
    int *begin, *end;
    void init(const int siz) {
        static int pool[N * 2], *curr = pool;
        end = begin = curr;
        curr += siz;
    }
    inline void push_back(const int x) {
        *end++ = x;
    }
} g[N];
#define adj(u) tmps = g[u].begin; tmpt = g[u].end; for (int *it = tmps; it != tmpt; ++it)
inline void upd(Data &fir, Data &sec, const Data &v) {
    if (v > fir)
        sec = fir, fir = v;
    else if (v > sec)
        sec = v;
}
inline void upd(const int u, const Data &v) {
    upd(d1[u], d2[u], v);
}
//   a_v - d(u, v) = a_v - (dep_u + dep_v - 2 * dep_u)
// = a_v - dep_v + dep_u
void dfs1(const int u, const int fa) {
    static Data d;
    int *tmps, *tmpt, v;
    adj (u) if ((v = *it) != fa) {
        dfs1(v, u);
        --(d = d1[v]).val;
        upd(u, std::max(d, Data(w[v] - 1, v)));
    }
}
void dfs2(const int u, const int fa) {
    int *tmps, *tmpt, v;
    Data fir = d1[u], sec = d2[u];
    upd(fir, sec, std::max(d3[u], Data(w[u], u)));
    --fir.val;
    --sec.val;
    adj (u) if ((v = *it) != fa) {
        if (fir.succ == v || fir.succ == d1[v].succ)
            d3[v] = sec;
        else
            d3[v] = fir;
        dfs2(v, u);
    }
}
 
int main() {
    static int i, len, seq[N], tim[N], deg[N], eu[N], ev[N];
    static ll m;
    n = io;
    m = io;
    rep (i, 1, n) {
        w[i] = io;
        d1[i] = d2[i] = d3[i] = DATA_MIN;
    }
    re (i, 1, n) {
        ++deg[eu[i] = io];
        ++deg[ev[i] = io];
    }
    rep (i, 1, n)
        g[i].init(deg[i]);
    re (i, 1, n) {
        g[eu[i]].push_back(ev[i]);
        g[ev[i]].push_back(eu[i]);
    }
    dfs1(1, -1);
    dfs2(1, -1);
    for (i = 1; !tim[i]; tim[i] = len, i = std::max(d1[i], d3[i]).succ)
        seq[len++] = i;
    i = tim[i] - 1;
    io.print(seq[m > i ? i + (m - i) % (len - i) : m]);
    io.flush();
 
    return 0;
}
