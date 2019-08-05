#include <cstdio>
#include <cstring>
#include <algorithm>
#define LC(o) ((o) << 1)
#define RC(o) (((o) << 1) | 1)

int c;
unsigned int seed, ans_sum = 0;
unsigned int randnum(){
    seed^=seed<<13;
    seed^=seed>>17;
    seed^=seed<<5;
    return seed;
}

inline int read(int &x){scanf("%d",&x);return x;}
inline void init_case(int &m,int &a,int &b,int &d,int p[]){
    static int i;
    scanf("%d%u%d%d%d%d",&m,&seed,&a,&b,&c,&d);
    for(i=1;i<=m;i++){
        if(randnum()%c==0)p[i]=-1;
        else p[i]=randnum()%b;
    }
}
const static unsigned int mod=998244353;
/*
一开始请调用read(T)读入数据组数T
接下来每组数据开始时请调用init_case(m,a,b,d,p)读入m,a,b,d,p[]
每组数据开始时请用一个初始化为0的32位无符号整形变量ans_sum存储答案，然后对于每个i，
用32位无符号整形变量cur_ans存储第i次答案，并调用update_ans(ans_sum,cur_ans,i)更新。最后输出ans_sum即可。
*/
const int MAXM = 2000005;
int p[MAXM], m, a, b, d;
int que[MAXM << 1], hd, tl;
bool bought[MAXM << 1], owned[MAXM << 1];

struct Seg {
    int v, l, r;
} st[MAXM << 3];
int lind[MAXM << 1];
void build(int o, int l, int r) {
    Seg &seg = st[o];
    seg.v = 0;
    seg.l = l;
    seg.r = r;
    int mid = (l + r) >> 1;
    if (l == r) {
        seg.v = l - 1 <= a ? -1 : 1;
        lind[l] = o;
    } else {
        build(LC(o), l, mid);
        build(RC(o), mid + 1, r);
        if (st[LC(o)].v == -1)
            seg.v = (st[RC(o)].v == -1) ? -1 : (st[RC(o)].v + mid - l + 1);
        else
            seg.v = st[LC(o)].v;
    }
}
void update(int i, int x) {
    static int o;
    o = lind[i];
    st[o].v = x;
    for (o >>= 1; o; o >>= 1) {
        Seg &seg = st[o];
        if (st[LC(o)].v == -1)
            seg.v = (st[RC(o)].v == -1) ? -1 : (st[RC(o)].v + st[LC(o)].r - st[LC(o)].l + 1);
        else
            seg.v = st[LC(o)].v;
    }
}
/*
void update(int o, int x, int v) {
    Seg &seg = st[o];
    upd(seg.v, v);
    if (seg.r < x || seg.l > x)
        return;
    if (seg.l == x && seg.r == x)
        return;
    int mid = (seg.l + seg.r) >> 1;
    if (mid >= x)
        update(LC(o), x, v);
    else
        update(RC(o), x, v);
}*/
int query(int o, int l, int r) {
    Seg &seg = st[o];
    if (seg.l > r || seg.r < l)
        return -1;
    if (l <= seg.l && seg.r <= r)
        return seg.v;
    int rl = query(LC(o), l, r), rr = query(RC(o), l, r);
    if (rl == -1)
        return (rr == -1) ? -1 : (rr + st[LC(o)].r - st[LC(o)].l + 1);
    return rl;
}

int main() {
    static int t, ks, i, x, y, cur_ans;
    read(t);
    for (ks = 0; ks < t; ++ks) {
        ans_sum = 0;
        init_case(m, a, b, d, p);
        hd = 1;
        tl = 0;
        build(1, 1, b);
        if (ks > 0) {
            memset(que, 0, sizeof(que));
            memset(bought, false, sizeof(bought));
            memset(owned, false, sizeof(owned));
        } // 初始有 [0, a]
        for (i = 0; i <= a; ++i)
            owned[i] = true;
        for (i = 1; i <= m; ++i) {
            x = p[i];
            // printf("p[%d] = %d\n", i, x);
            if (x == -1) {
                if (d == 1)
                    cur_ans = 0;
                else {
                    if (tl - hd + 1 > 0) {
                        y = que[hd++];
                        owned[y] = true;
                        update(y + 1, -1);
                        cur_ans = query(1, 1, b) - 1;
                    } else
                        cur_ans = 0;
                }
            } else if (x > a && !bought[x]) {
                bought[x] = true;
                owned[x] = true;
                update(x + 1, -1);
                cur_ans = query(1, 1, b) - 1;
            } else if (d == 1) {
                cur_ans = 0;
            } else if (owned[x]) {
                owned[x] = false;
                que[++tl] = x;
                update(x + 1, 1);
                cur_ans = query(1, 1, x + 1) - 1;
            } else {
                if (tl - hd + 1 > 0) {
                    y = que[hd++];
                    owned[y] = true;
                    update(y + 1, -1);
                    cur_ans = query(1, 1, b) - 1;
                } else
                    cur_ans = 0;
            }
            if (cur_ans < 0)
                cur_ans = b;
            // printf("ans[%d] = %d\n", i, cur_ans);
            // update_ans((unsigned int)cur_ans, i);
            ans_sum^=(long long)i*(i+7)%mod*((unsigned int)cur_ans)%mod;
        }
        printf("%u\n", ans_sum);
    }
    return 0;
}
