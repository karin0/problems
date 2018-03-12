#include<cstdio>
#include <vector>
#include <algorithm>
const int maxn=100005;
typedef long long ll;
int n,k,m;
ll aa[maxn],s[maxn],of[maxn],nf[maxn];
inline bool lesss(int p, int q, int x) { // assert p <= q
    if (p > q)
		        std::swap(p, q);
				    return (of[p] - (ll)s[p] * s[p] - of[q] + (ll)s[q] * s[q]) > ((ll)(s[p] - s[q]) * x);
}
inline bool less_slope(int p1, int q1, int p2, int q2) { // assert both p <= q
    return ((of[p1] - (ll)s[p1] * s[p1] - of[q1] + (ll)s[q1] * s[q1]) * ((ll)(s[p2] - s[q2]))) < 
	           ((of[p2] - (ll)s[p2] * s[p2] - of[q2] + (ll)s[q2] * s[q2]) * ((ll)(s[p1] - s[q1])));
}
std::vector<bool> vec;

int main()
{
    int he,ta;
    static ll qu[maxn];
	scanf("%d%d",&n,&m);
	int cnt=0;
	ll tmp;
	for(int i=1;i<=n;++i){
		scanf("%lld",&tmp);
		if(tmp)
			++cnt,s[cnt]=s[cnt-1]+tmp;
	}
	n=cnt;
	for(int j=1;j<=m;++j){
		//for(int i=1;i<=n;++i) swap(of[i],nf[i]);
        std::swap(of,nf);
		he=1,ta=0;
		for(int i=1;i<=n;++i){
			while(he<ta&&!lesss(qu[he],qu[he+1],-s[i])) he++;
			nf[i]=of[qu[he]]+s[qu[he]]*(s[i]-s[qu[he]]);
			while(he<ta&&less_slope(qu[ta-1],qu[ta],qu[ta],i)) 
				ta--;
			qu[++ta]=i;
		}
//		swap(of,nf);
	}
	printf("%lld\n",nf[n]);
	return 0;
}
