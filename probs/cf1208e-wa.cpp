#include <akari>

IO<1000000, 1000000> io;

cint N = 1000003;

int a[N], w, l;
ll c[N];
inline void add(int ql, int qr, int i) {
    ccc("Adding", ql, qr, i);
    if (a[i] < 0) {
        ql = std::max(ql, l + 1);
        qr = std::min(qr, w - l);
        if (ql > qr)
            return;
    }
    c[ql] += a[i];
    c[qr + 1] -= a[i];
}

int prev[N], sta[N];
int main() {
    int n;
    io > n > w;
    rep (k, 1, n) {
        //rep (i, 1, w)
        //    c[i] = 0;

        io > l;
        int siz = 0;
        rep (i, 1, l) {
            io >> a[i];
            while (siz && a[sta[siz]] <= a[i])
                --siz;
            prev[i] = sta[siz];
            sta[++siz] = i;
        }
        siz = 0;
        per (i, l, 1) {
            while (siz && a[sta[siz]] < a[i])
                --siz;
            int nxt = sta[siz];
            sta[++siz] = i;
            cint pre = prev[i];
            ccc(i, pre, nxt);
            int l1 = i, r1 = nxt - 1;
            if (pre) {
                int l2 = w - l + pre + 1, r2 = w - l + i;
                if (nxt) {
                    if (l1 <= l2 && r2 <= r1)
                        continue;
                    else if (l2 <= l1 && r1 <= r2)
                        l1 = l2, r1 = r2;
                    else {
                        if (l1 > l2) {
                            std::swap(l1, l2);
                            std::swap(r1, r2);
                        }
                        if (l2 > r1)
                            add(l2, r2, i);
                        else
                            r1 = r2;
                    }
                    add(l1, r1, i);
                } else
                    add(l2, r2, i);
            } else if (nxt)
                add(l1, r1, i);
            else
                add(i, w - l + i, i);
        }
    }
    ll ans = 0;
    re (i, 1, w)
        io << (ans += c[i]) << ' ';
    io << (ans + c[w]) << '\n';
}
