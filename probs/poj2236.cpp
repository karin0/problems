/*
POJ 2236
AC
并查集
*/
#include <cstdio>
#include <algorithm>
using namespace std;

int n, sqd, d, no, ldx, nindex, sqtd, par[1010], rank[1010], px[1010], py[1010];
int index[1010], pindex[1010];
bool able[1010];

int find(int x) {
    int p=par[x];
    if (p==x) return x;
    return par[x]=find(p);
}

void unite(int x, int y) {
    x=find(x); y=find(y);
    if (x==y) return;
    if (rank[x]<rank[y]) par[x]=y;
    else {
        par[y]=x;
        if (rank[x]==rank[y]) rank[x]++;
    }
}

bool cmp(int x, int y) {
    return px[x]<px[y];
}

inline int sq(int x) {return x*x;}

int main(){
    scanf("%d%d", &n, &d);
    for (int i=1; i<=n; i++) {
        scanf("%d%d", px+i, py+i);
        par[i]=i;
        index[i]=i;
    }
    
    sqd=sq(d);
    sort(index+1, index+n+1, cmp);
    for (int i=1; i<=n; i++) pindex[index[i]]=i;
    char oper;
    int p, q;
    while (scanf("%c%d", &oper, &p)!=EOF) {
        switch (oper) {
            case 'O':
                able[p]=true;
                nindex=pindex[p]-1;
                no=index[nindex];
                ldx=px[p]-px[no];
                while (ldx<=d&&nindex>=1) {
                    if (able[no]) {
                        sqtd=sq(px[p]-px[no])+sq(py[p]-py[no]);
                        if (sqtd<=sqd) unite(no, p);
                    }
                    nindex--;
                    no=index[nindex];
                    ldx=px[p]-px[no];
                }
                nindex=pindex[p]+1;
                no=index[nindex];
                ldx=px[no]-px[p];
                while (ldx<=d&&nindex<=n) {
                    if (able[no]) {
                        sqtd=sq(px[p]-px[no])+sq(py[p]-py[no]);
                        if (sqtd<=sqd) unite(no, p);
                    }
                    nindex++;
                    no=index[nindex];
                    ldx=px[p]-px[no];
                }
                break;
            case 'S':
                scanf("%d", &q);
                printf( (find(p)==find(q)) ? "SUCCESS\n" : "FAIL\n");
                break;
        }
    }
    
    return 0;
}
