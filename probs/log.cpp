#include <cstdio>
#include <cstring>
#include <algorithm>
int c;
unsigned int seed, ans_sum = 0;
unsigned int randnum(){
    seed^=seed<<13;
    seed^=seed>>17;
    seed^=seed<<5;
    return seed;
}
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
int m, a, b, d;
bool bought[MAXM << 1], owned[MAXM << 1];

namespace Mono {
    int val[MAXM], mono[MAXM], hd, tl;
    void clear() {
        hd = 1;
        tl = 0;
        memset(val, 0, sizeof(val));
    }
    void push(int x, int t) { // while removing
        while (tl - hd + 1 > 0 && val[mono[tl]] >= x)
            --tl;
        mono[++tl] = t;
        val[t] = x;
    }
    void pop(int t) {
        while (tl - hd + 1 > 0 && mono[hd] <= t)
            ++hd;
    }
    int top() {
        if (tl - hd + 1 <= 0)
            return 0x7f7f7f7f;
        return val[mono[hd]];
    }
}
int que[MAXM], hd, tl, dt[MAXM];

int main() {
    static int t, ks, i, x, y, cur_ans, p[MAXM], mex;
    scanf("%d", &t);
    for (ks = 0; ks < t; ++ks) {
        ans_sum = 0;
        init_case(m, a, b, d, p);
        hd = 1;
        tl = 0;
        mex = a + 1;
        Mono::clear();
        if (ks > 0) {
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
                        y = que[hd];
                        owned[y] = true;
                        Mono::pop(dt[hd++]);
                        cur_ans = std::min(Mono::top(), mex);
                    } else
                        cur_ans = 0;
                 }
            } else if (x > a && !bought[x]) {
                bought[x] = true;
                owned[x] = true;
                while (bought[mex])
                    ++mex;
                cur_ans = std::min(Mono::top(), mex);
            } else if (d == 1) {
                cur_ans = 0;
            } else if (owned[x]) {
                owned[x] = false;
                que[++tl] = x;
                dt[tl] = i;
                Mono::push(x, i);
                cur_ans = std::min(Mono::top(), mex);
            } else {
                if (tl - hd + 1 > 0) {
                    y = que[hd];
                    owned[y] = true;
                    Mono::pop(dt[hd++]);
                    cur_ans = std::min(Mono::top(), mex);
                } else
                    cur_ans = 0;
            }
            // printf("ans[%d] = %d, %d\n", i, cur_ans, (int)(cur_ans == mex));
            // update_ans((unsigned int)cur_ans, i);
            ans_sum^=(long long)i*(i+7)%mod*((unsigned int)cur_ans)%mod;
        }
        printf("%u\n", ans_sum);
    }
    return 0;
}
