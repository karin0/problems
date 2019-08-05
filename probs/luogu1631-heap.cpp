#include <akari>

IO<1000000, 1000000> io;

cint N = 100002;

struct S {
    int s, p;
    bool operator < (const S &rhs) const {
        return s > rhs.s;
    }
};
std::priority_queue<S> q;
int a[N], b[N], c[N];
int main() {
    int n = io;
    rep (i, 1, n)
        io >> a[i];
    rep (i, 1, n) {
        io >> b[i];
        q.push((S){a[c[i] = 1] + b[i], i});
    }
    while (n--) {
        S x = q.top();
        q.pop();
        q.push((S){a[++c[x.p]] + b[x.p], x.p});
        io << x.s << ' ';
    }
    io << '\n';

    return 0;
}
