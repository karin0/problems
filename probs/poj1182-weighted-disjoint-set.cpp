/*
POJ 1182
AC
加权并查集;向量偏移
*/
#include <cstdio>
using namespace std;

int fa[50020], r[50020];
int find(int x) {
    int f=fa[x];
    if (f==x) return f;
    fa[x]=find(f);
    r[x]=(r[x]+r[f])%3; // 偏移
    return fa[x];
}
void merge(int x, int y, int d) {
    int fx=find(x), fy=find(y);
    fa[fx]=fy;
    r[fx]=(r[y]+d-r[x]+3)%3; // 偏移
}
bool same(int x, int y) {
    return find(x)==find(y);
}

int main() {
    int n, k, d, x, y, ans=0;
    scanf("%d%d", &n, &k);
    for (int i=1; i<=n; i++) {
        fa[i]=i;
    }
    while (k--) {
        scanf("%d%d%d", &d, &x, &y);
        d--; 
        // Rel(x, y): 0 表示 X 与 Y 为同种, 1 表示 X 吃 Y, 2 表示 X 被 Y 吃
        // 等同于食物链上 X 与 Y 的种类的距离
        // r[x]=Rel(x, fa[x])
        if (x>n||y>n || (same(x, y) && (r[y]+d)%3 != r[x])) { // 短路
            ans++;
        } else {
            merge(x, y, d);
        }
    }
    printf("%d\n", ans);
    return 0;
}
