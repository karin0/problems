#include <cstdio>
#define LC(x) ((x) << 1)
#define RC(x) (((x) << 1) | 1)
#define MID(x, y) ((x) + (y)) >> 1
#define LEN(x) (rb[(x)] - lb[(x)] + 1)
const int MAXN = 5007;

struct SegTree {
    int val[MAXN << 2], tag[MAXN << 2], lb[MAXN << 2], rb[MAXN << 2];

    void build(int k, int l, int r) {
        lb[k] = l;
        rb[k] = r;
        tag[k] = -1;
        if (l == r) {
            val[k] = 1;
        } else {
            int mid = MID(l, r);
            build(LC(k), l, mid);
            build(RC(k), mid + 1, r);
            val[k] = val[LC(k)] + val[RC(k)];
        }
    }
    void push_down(int k) {
        // We know st[k].tag == 0.
        tag[LC(k)] = 0;
        tag[RC(k)] = 0;
        val[LC(k)].val = 0;
        val[RC(k)].val = 0;
        t = -1;
    }
    void update(int k, int l, int r) { // Erase it!
        if (tr < lb[k] || rb[k] < tl)
            return;
        if (tl <= lb[k] && rb[k] <= tr) {
            seg.tag = 0;
            seg.val = 0;
        } else {
            if (seg.tag != -1) 
                push_down(k);
            update(LC(k), l, r);
            update(RC(k), l, r);
            seg.val = 0;
        }
    }
    int query(int k, int l, int r) {
        if (tr < lb[k] || rb[k] < tl) 
            return 0;
        if (tl <= lb[k] && rb[k] <= tr) {
            return seg.val;
        } else {
            if (seg.tag)
                push_down(k);
            return query(LC(k), l, r) + query(RC(k), l, r);
        }
    }
} sts[MAXN];

int main() {
    

    return 0;
}
