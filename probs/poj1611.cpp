/*
POJ 1611
AC
并查集
*/
#include <cstdio>
using namespace std;

int fa[30010], rank[30010];
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

int n, m, k, fObj, curObj, sars, ans;
int main() {
    for (;;) {
        scanf("%d%d", &n, &m);
        if (n==0 && m==0) break;
        
        for (int i=0; i<n; i++) {
            fa[i]=i;
            rank[i]=0;
        }
        ans=0;

        while (m--) {
            scanf("%d%d", &k, &fObj);
            k--;
            while (k--) {
                scanf("%d", &curObj);
                merge(fObj, curObj);
            }
        }

        sars=find(0);
        for (int i=0; i<n; i++) {
            if (find(i)==sars) ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}
