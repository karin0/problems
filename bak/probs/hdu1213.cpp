/*
HDU 1213
AC 
并查集
*/
#include <cstdio>
using namespace std;

int fa[1010], rank[1010];
int find(int x) {
    int f=fa[x];
    if (f==x) return f;
    return fa[f]=find(f);
}
void merge(int x, int y) {
    x=find(x);
    y=find(y);
    if (rank[x]<rank[y]) fa[x]=y;
    else {
        fa[y]=x;
        if (rank[x]==rank[y]) rank[x]++;
    }
}

int t, m, n, a, b, ans;
int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        for (int i=1; i<=n; i++) {
            fa[i]=i;
            rank[i]=0;
        }
        ans=0;

        while (m--) {
            scanf("%d%d", &a, &b);
            merge(a, b);
        }
        for (int i=1; i<=n; i++) {
            if (fa[i]==i) ans++; // 父节点为根节点的节点个数为不相交的集合数
        }
        printf("%d\n", ans);
    }
    return 0;
}
