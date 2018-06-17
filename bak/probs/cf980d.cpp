nclude <cstdio>
#include <cctype>
#include <algorithm>
#include <cmath>
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
        return *s++; // return s == t ? EOF : *s++;
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
            fwrite(p = b, 1, L, stdout);
        *p++ = c;
    }
    template<class T>
    void print(T x) {
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
    }
    inline void flush() const {
        fwrite(b, 1, p - b, stdout); // p = b;
    }
} io;

const int N = 5003;
int n, fa[N], rk[N];
int find(int x)
{
    static int k, j, r;
    r = x;
    while (r != fa[r])
        r = fa[r];
    k = x;
    while (k != r) {
        j = fa[k]; 
        fa[k] = r;
        k = j;
    }
    return r;
}
void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y)
        return;
    if (rk[x] > rk[y])
        std::swap(x, y);
    fa[x] = y;
    if (rk[x] == rk[y])
        ++rk[y];
}
bool vis[N][N];

int main() {
    static int i, j, t;
    static long long x, a[N], y;
    n = io;
    rep (i, 1, n) {
        a[i] = io;
        fa[i] = i;
    }
    rep (i, 1, n) {
		if (a[i] == 0)
			continue;
        re (j, 1, i) {
			if (a[j] == 0)
				continue;
            x = a[i] * a[j];
            if (x < 0)
                continue;
            y = sqrt(x);
            if (y * y == x) {
                unite(i, j);
            }
        }
    }
    static int cnt, ans[N];
    static bool *vi;
    rep (i, 1, n) {
        cnt = 0;
        vi = vis[i];
        rep (j, i, n) {
			if (a[j] != 0) {
				t = find(j);
				if (!vi[t])
					vi[t] = true, ++cnt;
			}
            ++ans[cnt];
        }
    }
	static bool flag;
	static int len;
	rep (i, 1, n) {
		if (a[i] == 0) {
			if (flag)
				++len;
			else
				flag = true, len = 1;
		} else {
			if (flag) {
				flag = false;
				ans[1] += len + ((len * (len - 1)) >> 1);
				len = 0;
			}			
		}
	}
	if (flag) {
		flag = false;
		ans[1] += len + ((len * (len - 1)) >> 1);
		len = 0;
	}		
    rep (i, 1, n) {
        io.print(ans[i]);
        io.pc(i == n ? '\n' : ' ');
    }

    io.flush();
    return 0;
}
