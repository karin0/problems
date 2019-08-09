#include <akari>

IO<1000000, 1000> io;

cint N = 100002, T = N << 1;

int c[T], maxt, E[N], L[N], C[N];
ll d[T];
inline void add(int i) {
    for (int v = i; i <= maxt; i += i & -i) {
        ++c[i];
        d[i] += v;
    }
}
inline void dec(int i) {
    for (int v = i; i <= maxt; i += i & -i) {
        --c[i];
        d[i] -= v;
    }
}

int rc;
ll rd;
inline void qry(int i) {
    for (i = std::min(i, maxt), rd = rc = 0; i; i -= i & -i) { // ***
        rc += c[i];
        rd += d[i];
    }
}

std::set<int> s;
std::set<int>::iterator iter[T];
inline void ins(int t) {
    if (!s.empty()) {
        auto it = s.lower_bound(t);
        if (it == s.begin()) {
            int x = *it - t;
            add(x);
        } else if (it == s.end()) {
            int x = t - *std::prev(it);
            add(x);
        } else {
            int x = *it - t, y = t - *std::prev(it);
            add(x);
            add(y);
            dec(x + y);
        }
    }
    iter[t] = s.insert(t).first;
}
inline void del(int t) {
    // auto it = s.find(t);
    auto it = iter[t];
    if (s.size() > 1) {
        if (it == s.begin()) {
            int x = *std::next(it) - t;
            dec(x);
        } else if (it == std::prev(s.end())) {
            int x = t - *std::prev(it);
            dec(x);
        } else {
            int x = *std::next(it) - t, y = t - *std::prev(it);
            dec(x);
            dec(y);
            add(x + y);
        }
    }
    s.erase(it);
}

std::vector<int> z[N];
int main() {
    int T;
    io >> T;
    rep (ks, 1, T) {
        int n, m;
        io >> n;
        rep (i, 1, n)
            io >> E[i] >> L[i] >> C[i];
        io >> m;
        int t;
        while (m--) {
            int l, r;
            io >> t >> l >> r;
            z[l].push_back(t);
            if (r < n) // ***
                z[r + 1].push_back(-t);
        }
        maxt = t;
        ll ans = 0;
        rep (i, 1, n) {
            for (int x : z[i])
                x > 0 ? ins(x) : del(-x);
            z[i].clear();
            if (s.empty())
                continue;
            ans += std::min((ll)C[i], E[i] + (ll)L[i] * *s.begin());
            if (L[i]) {
                qry(C[i] / L[i]);
                ans += L[i] * rd + (ll)C[i] * ((int)s.size() - 1 - rc);
            }
        }
        io << "Case #" << ks << ": " << ans daze;
        if (ks < T) {
            s.clear();
            rep (i, 1, maxt)
                d[i] = c[i] = 0;
            maxt = 0;
        }
    }    
    
    return 0;
}
