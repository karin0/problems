#include <akari>

IO<1000000, 1000000> io;

cint p = 1000000000, p1 = 512, p2 = 1953125, l1 = 768, l2 = 7812500, u1 = 2, u2 = 4, d1 = 1, d2 = 0;
cll t1 = 212890625, t2 = 787109376, v1 = 256, v2 = 390625;

template <class T, int p>
inline int qpow(T a, int n) {
    T res = 1;
    for (; n; n >>= 1, a = a * a % p)
        if (n & 1)
            res = res * a % p;
    return res;
}

int n, m;

/*
template <int p, int l>
void c() {
    int a = 0, b = 1, s = 1;
    rep (i, 3, l) {
        int c = a + b;
        if (c >= p)
            c -= p;
        a = b;
        b = c;
        s += qpow<ll, p>(c, m);
        if (s >= p)
            s -= p;
    }
    ccc(p, l, s, m);
}
*/

template <class T, int p, int l, int u, int d, ll v, ll t>
ll calc() {
    int k = n / l, r = n - k * l, s = 1;
    if (m % u == d)
        s = (s + k * v) % p;
    if (r == 1) return (s - 1) * t;
    if (r == 2) return s * t;
    int a = 0, b = 1;
    rep (i, 3, r) {
        int c = a + b;
        if (c >= p)
            c -= p;
        a = b;
        b = c;
        s += qpow<T, p>(c, m);
        if (s >= p)
            s -= p;
    }
    return s * t;
} 

int main() {
    io > n > m;
    ++n;
    (io < int((calc<int, p1, l1, u1, d1, v1, t1>() + calc<ll, p2, l2, u2, d2, v2, t2>()) % p)) daze;
}
