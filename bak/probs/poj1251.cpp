/*
POJ 1251
AC
图;最小生成树;Kruskal;模板
0ms;392K
*/
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN=35, MAXM=85;
int n, fa[MAXN], rank[MAXN]; // 0 .. n-1


int f;
int find(int x) {
    f=fa[x];
    if (f==x) return f;
    return fa[x]=find(f);
}
void merge(int x, int y) {
    x=find(x);
    y=find(y);
    if (rank[x]>rank[y]) fa[y]=x;
    else {
        fa[x]=y;
        if (rank[x]==rank[y]) ++rank[y];
    }
}
bool same(int x, int y) {
    return find(x)==find(y);
}

int m;
int va[MAXM], vb[MAXM], w[MAXM]; // 0 .. m-1

bool cmp(int ea, int eb) {
    return w[ea]<w[eb];
}

int eids[MAXM], e;
int krus() {
    int ans=0;
    for (int i=0; i<n; ++i) {
        fa[i]=i;
    }
    memset(rank, 0, sizeof(rank));

    for (int i=0; i<m; ++i) {
        eids[i]=i;
    }
    sort(eids, eids+m, cmp);
    for (int i=0; i<m; ++i) {
        e=eids[i];
        if (!same(va[e], vb[e])) {
            ans+=w[e];
            merge(va[e], vb[e]);
        }
    }
    return ans;
}

int k, cost;
char tmp;
int main() {
    for (;;) {
        scanf("%d", &n);
        if (n==0) break;
        m=-1;
        --n;
        for (int u=0; u<n; u++) {
            scanf("%s%d", &tmp, &k); // %s　读取字符
            while (k--) {
                scanf("%s%d", &tmp, &cost);
                ++m;
                va[m]=u;
                vb[m]=tmp-'A';
                w[m]=cost;
            }
        }
        ++n;
        ++m; // 为边数
        printf("%d\n", krus());
    }
    return 0;
}
