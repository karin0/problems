#include <cctype>
#include <iostream>
#include <algorithm>

#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)
#define pe(i_, s_, t_) for (int i_ = (s_); i_ > (t_); --i_)
#define daze << '\n'

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
    #define ccf(args...) std::fprintf(stderr, args)
    #define crep(i_, s_, t_) rep(i, s_, t_)
#else
    #define ccc(...) 0
    #define ccf(...) 0
    #define crep(...) if (0)
#endif

typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef const int cint;
typedef const ll cll;
typedef const char cchar;

template <int I, int O>
struct IO {
    char r[20];
#ifdef AKARI
    char gc() {
        return std::getchar();
    }
    void pc(cchar c) {
        std::putchar(c);
    }
#else
    char a[I], b[O], *s, *t, *z;
    std::streambuf *i, *o;
    IO() : z(b) {
        std::ios::sync_with_stdio(false);
        if (I) std::cin.tie(NULL), i = std::cin.rdbuf();
        if (O) std::cout.tie(NULL), o = std::cout.rdbuf();
    }
    ~IO() {
        if (O) o->sputn(b, z - b);
    }
    char gc() {
        if (s == t) t = (s = a) + i->sgetn(a, I);
        return *s++;
    }
    void pc(cchar c) {
        if (z == b + O) o->sputn(z = b, O);
        *z++ = c;
    }
#endif
    char *gs(char *p) {
        char c;
        while (!std::isgraph(c = gc()));
        while (*p++ = c, std::isgraph(c = gc()));
        return *p = 0, p;
    }
    IO &operator >> (char *p) {
        char c;
        while (!std::isgraph(c = gc()));
        while (*p++ = c, std::isgraph(c = gc()));
        return *p = 0, *this;
    }
    IO &operator >> (char &c) {
        while (!std::isgraph(c = gc()));
        return *this;
    }
    template <class T>
    IO &operator >> (T &x) {
        char c;
        while (!std::isdigit(c = gc()) && c != '-');
        if (c == '-')
            for (x = '0' - gc(); std::isdigit(c = gc()); x = x * 10 + ('0' - c));
        else
            for (x = c - '0'; std::isdigit(c = gc()); x = x * 10 + (c - '0'));
        return *this;
    }
    template <class T>
    operator T () {
        T x;
        return *this >> x, x;
    }
    IO &operator << (char *p) {
        while (*p) pc(*p++);
        return *this;
    }
    IO &operator << (cchar *p) {
        while (*p) pc(*p++);
        return *this;
    }
    IO &operator << (cchar c) {
        return pc(c), *this;
    }
    template <class T>
    IO &operator << (T x) {
        if (x < 0) pc('-'), x = -x;
        else if (x == 0) return pc('0'), *this;
        char *j = r;
        while (*j++ = x % 10 + '0', x /= 10);
        while (pc(*--j), j != r);
        return *this;
    }
};

IO<1000000, 100> io;

cint N = 100002;

int fa[N], siz[N];

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

struct Edge {
    int u, v, w;
    bool operator < (const Edge &rhs) const {
        return w < rhs.w;
    }
} a[N];

int main() {
    int T;
    io >> T;
    while (T--) {
        int n;
        io >> n;
        ll ans = 0;
        re (i, 1, n) {
            Edge &e = a[i];
            io >> e.u >> e.v >> e.w;
            ans += e.w;
            fa[i] = i;
            siz[i] = 1;
        }
        fa[n] = n;
        siz[n] = 1;
        std::sort(a + 1, a + n);
        re (i, 1, n) {
            Edge &e = a[i];
            int u = find(e.u);
            int v = find(e.v);
            // assert(u != v);
            // cccc(e.u, e.v, e.w, u, v, siz[u], siz[v], ans);
            ans += ((ll)siz[u] * siz[v] - 1) * (e.w + 1);
            siz[v] += siz[u];
            fa[u] = v;
        }
        io << ans daze;
    }
}
