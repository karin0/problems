// 模数须为奇素数
#include <akari>
#include <cstdlib>
#include <ctime>

typedef long long ll;

int p, w;

struct S {
    int x, y;
    S(int x, int y) : x(x), y(y) {}
    S operator * (const S &r) const {
        return S(
            ((ll)x * r.x + (ll)y * r.y % p * w) % p,
            ((ll)x * r.y + (ll)y * r.x) % p
        );
    }
};

inline int qpow(ll a, int n) {
    ll r = 1;
    for (; n; n >>= 1, a = a * a % p)
        if (n & 1)
            r = r * a % p;
    return r;
}

inline int qpow(S a, int n) {
    S r = S(1, 0);
    for (; n; n >>= 1, a = a * a)
        if (n & 1)
            r = r * a;
    return r.x;
}

inline int solve(int n) { // 求出一个解 x，另一解为 p-x
    n %= p;
    int t = p >> 1; // (p - 1) / 2
    if (qpow(n, t) == p - 1)
        return -1;
    while (true) {
        int a = rand() % p;
        w = ((ll)a * a % p - n) % p;
        if (w < 0)
            w += p;
        if (qpow(w, t) == p - 1)
            return qpow(S(a, 1), t + 1);
    }
}

io_t io;

int main() {
    srand(time(0));
    int T;
    io >> T;
    while (T--) {
        int n;
        io >> n >> p;
        if (!n) {
            io << "0\n";
            continue;
        }
        int x = solve(n);
        if (x == -1) {
            io << "Hola!\n"; // 无解
            continue;
        }
        int y = p - x;
        if (x > y)
            io << y << ' ' << x daze;
        else
            io << x << ' ' << y daze; 
    }
}