#include <akari>

IO<1000000, 1000000> io;

cint N = 200002;

int n;
ll bit[N];
inline void add(int i, int v) {
    for (; i <= n; i += i & -i)
        bit[i] += v;
}
inline ll qry(int i) {
    ll res = 0;
    for (; i; i -= i & -i)
        res += bit[i];
    return res;
}

ll s[N];
int p[N];
int main() {
    io > n;
    rep (i, 1, n) {
        io > s[i];
        add(i, i);
    }
    per (i, n, 1) {
        int l = 0, r = n;
        while (r - l > 1) {
            int mid = (l + r) >> 1;
            if (qry(mid) <= s[i])
                l = mid;
            else
                r = mid - 1;
        }
        if (qry(r) > s[i])
            r = l;
        p[i] = ++r;
        add(r, -r);
    }
    re (i, 1, n)
        (io - p[i]) << ' ';
    (io - p[n]) << '\n';
}
