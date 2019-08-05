/*
POJ 2492
AC
并查集
*/
#include <cstdio>
#include <cstring>
using namespace std;

int cmax, cAct, n, fa[2100], rank[2100], a, b;
bool cond[2100], hasHomo;
int find(int x) {
    int f=fa[x];
    if (x==f) return x;
    fa[x]=find(f); // Have to compress the path before update the cond
    cond[x]= cond[x]==cond[f]; // Process the cond
    return fa[x];
}
void merge(int x, int y) {
    int fx=find(x);
    int fy=find(y);
    if (fx==fy) return;
    if (rank[fx]>rank[fy]) {
        fa[fy]=fx;
        cond[fy]= cond[x]!=cond[y]; // Process the cond when merging. Do not use the root
    } else {
        fa[fx]=fy;
        if (rank[fx]==rank[fy]) rank[fy]++;
        cond[fx]= cond[x]!=cond[y]; // Process the cond
    }
}
bool same(int x, int y) {
    return find(x)==find(y);
}

int main() {
    scanf("%d", &cmax);
    for (int c=1; c<=cmax; c++) {
        hasHomo=false;
        printf("Scenario #%d:\n", c);
        scanf("%d%d", &n, &cAct);
        for (int i=1; i<=n; i++) {
            fa[i]=i;
            rank[i]=0;
            cond[i]=true; // If has the same gendar as the root
        }
        for (int i=0; i<cAct; i++) {
            scanf("%d%d", &a, &b);
            if (hasHomo) continue;
            if (same(a, b) && cond[a]==cond[b]) {
                hasHomo=true;
            } else {
                merge(a, b);
            }
        }
        printf(hasHomo ? "Suspicious bugs found!\n\n" : "No suspicious bugs found!\n\n");
    }
    return 0;
}
