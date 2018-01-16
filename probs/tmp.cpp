#include<bits/stdc++.h>
const int maxn=100005;
typedef long long ll;
int n,m,k,cnt;
ll aa[maxn],s[maxn],of[maxn],nf[maxn];
inline bool lsess(int p, int q, int x) { // assert p <= q
    return (of[p] - (ll)s[p] * s[p] - of[q] + (ll)s[q] * s[q]) > ((ll)(s[p] - s[q]) * x);
}
inline bool less_slope(int p1, int q1, int p2, int q2) { // assert both p <= q
    return ((of[p1] - (ll)s[p1] * s[p1] - of[q1] + (ll)s[q1] * s[q1]) * ((ll)(s[p2] - s[q2]))) <
           ((of[p2] - (ll)s[p2] * s[p2] - of[q2] + (ll)s[q2] * s[q2]) * ((ll)(s[p1] - s[q1])));
}
int main()
{
    static ll q[maxn];
    int hd,tl;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i){
        scanf("%lld",&aa[i]);
        if(aa[i])
            ++cnt,s[cnt]=s[cnt-1]+aa[i];
    }
    n=cnt;
    for(int ja=1;ja<=m;++ja){
        hd=1, tl = 0;
        std::swap(nf,of);
        //q[++ta]=0;
        for(int i=1;i<=n;++i){
            while (tl - hd + 1 > 1 && !lsess(q[hd], q[hd + 1], -s[i]))
                ++hd;
            k = q[hd];
            nf[i] = of[k] + (ll)(s[i] - s[k]) * s[k];
            while (tl - hd + 1 > 1 && less_slope(q[tl - 1], q[tl], q[tl], i))
                --tl;
            q[++tl] = i;

        }
    }
    printf("%lld\n",nf[n]);
    return 0;
}
    
