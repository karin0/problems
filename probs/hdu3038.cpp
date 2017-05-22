/*
HDU 3038
AC?
并查集，向量偏移
*/
#include <cstdio>
using namespace std;

int fa[200010], r[200010];
int sgn(bool x) {
    if (x) return 1;
    else return -1;
}
int find(int x) {
    int f=fa[x];
    if (f==x) return f;
    fa[x]=find(f);
    r[x]=r[x]+r[f];
    return fa[x];
}
void merge(int x, int y, int d) {
    int fx=find(x), fy=find(y);
    fa[fx]=fy; 
    r[fx]=r[y]+d-r[x];
}

int main() {
    int n, m, x, y, d, fx; 
    while (scanf("%d%d", &n, &m)!=EOF) {
        int ans=0;
        for (int i=1; i<=n; i++) {
            fa[i]=i;
            r[i]=0;
        } 
        while (m--) { 
            scanf("%d%d%d", &x, &y, &d);
            y++; // Sum of range [x, y) is d
            fx=find(x);
            if (fx==find(y) && r[x]-r[y]!=d) {
                ans++;
            } else {
                merge(x, y, d); // x <= y
            }
        }
        printf("%d\n", ans); 
    }
    return 0;
}
