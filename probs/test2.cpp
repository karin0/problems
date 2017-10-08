#include <cstdio>

const int MAXN = 1e6 + 10;

struct SegTree {
    struct Seg {
        int v, l, r;
    };
    Seg st[MAXN << 2];
    int a[MAXN];
    void build(int o, int l, int r) {
        Seg &seg = st[o];
        seg.l = l;
        seg.r = r;
        if (l == r)
            seg.v = a[l];
        
    }


};

int main() {


    return 0;
}
