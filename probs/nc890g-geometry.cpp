#include <akari>

IO<1000000, 0> io;

cint N = 100002;
const double eps = 1e-7;

template <class T>
struct Pt {
    T x, y;
    Pt() {}
    Pt(const T x, const T y) : x(x), y(y) {}
};
Pt<int> a[N], b[N];
inline Pt<double> mid(const Pt<int> &p, const Pt<int> &q) {
    return Pt<double>((p.x + q.x) / 2.0, (p.y + q.y) / 2.0);
}

struct Ln { // Ax + By + C = 0 for all C-s
    int a, b;
    Ln(cint a, cint b) : a(a), b(b) {}
    Ln(const Pt<int> &p, const Pt<int> &q) : a(p.y - q.y), b(q.x - p.x) {}
    ll operator () (const Pt<int> &p) const {
        return (ll)a * p.x + (ll)b * p.y;
    }
    double operator () (const Pt<double> &p) const {
        return a * p.x + b * p.y;
    }
    Ln normal() const {
        return Ln(b, -a);
    }
};

double ans;
int n, h1, h2;
inline void calc(const Ln l) {
    auto cmp = [&](const Pt<int> &p, const Pt<int> &q) {
        return l(p) < l(q);
    };
    std::nth_element(b + 1, b + h1, b + n + 1, cmp);
    const auto p = b[h1];
    std::nth_element(b + 1, b + h2, b + n + 1, cmp);
    double c = -l(mid(p, b[h2]));
    rep (i, 1, n)
        if (fabs(l(b[i]) + c) < eps)
            return;
    ans = std::max(ans, std::abs(l(p) + c) / sqrt((ll)l.a * l.a + (ll)l.b * l.b));
    // ccc(l.a, l.b, c, p.x, p.y, b[h2].x, b[h2].y, ans);
}

int main() {
    io >> n;
    h1 = n >> 1, h2 = h1 + 1;
    rep (i, 1, n)
        io >> a[i].x >> a[i].y;
    memcpy(b + 1, a + 1, n * sizeof(*a));
    rep (i, 1, n) re (j, 1, i) {
        Ln l = Ln(a[i], a[j]);
        calc(l);
        calc(l.normal());
    }

    printf("%.12f\n", ans);

    return 0;
}
