#include <akari>

IO<1000000, 1000000> io;

cint N = 1002;

int n, k, a[N];
std::multiset<int> s;
bool check(int x) {
    s.clear();
    rep (i, 1, n)
        s.insert(a[i]);
    rep (i, 1, k) {
        int vol = x;
        while (vol) {
            auto it = s.upper_bound(vol);
            if (it == s.begin())
                break;
            --it;
            vol -= *it;
            s.erase(it);
            if (s.empty())
                return true;
        }
    }
    return false;
}

int main() {
    int t;
    io >> t;
    rep (ks, 1, t) {
        io >> n >> k;
        int sum = 0;
        rep (i, 1, n) {
            io >> a[i];
            sum += a[i];
        }
        int i;
        for (i = ceil((double)sum / k); !check(i); ++i);
        io << "Case #" << ks << ": " << i daze;
    }
    
    return 0;
}

int n, k, a[N];