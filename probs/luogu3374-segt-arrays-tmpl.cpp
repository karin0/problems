#include <akari>

IO<1000000, 1000000> io;

cint N = 500002;

#define lc(o) (o << 1)
#define rc(o) ((o << 1) | 1)

ll sum[N * 4];
void maintain(cint o) {
    sum[o] = sum[lc(o)] + sum[rc(o)];
}
void update(cint o, cint l, cint r, cint i, cll x) {
    if (l == r) {
        sum[o] += x;
        return;
    }
    int mid = (l + r) >> 1;
    if (i <= mid)
        update(lc(o), l, mid, i, x);
    else
        update(rc(o), mid + 1, r, i, x);
    maintain(o);
}
ll query(cint o, cint l, cint r, cint ql, cint qr) {
    if (ql <= l && r <= qr)
        return sum[o];
    int mid = (l + r) >> 1;
    ll ret = 0;
    if (ql <= mid)
        ret += query(lc(o), l, mid, ql, qr);
    if (qr > mid)
        ret += query(rc(o), mid + 1, r, ql, qr);
    return ret;
}
void build(cint o, cint l, cint r) {
    if (l == r) {
        io >> sum[o];
        return;
    }
    int mid = (l + r) >> 1;
    build(lc(o), l, mid);
    build(rc(o), mid + 1, r);
    maintain(o);
}

int main() {
    int n, m;
    io >> n >> m;
    build(1, 1, n);
    while (m--) {
        char op = io;
        int x = io;
        if (op == '1')
            update(1, 1, n, x, io);
        else
            io << query(1, 1, n, x, io) daze;
    }
    
    return 0;
}
