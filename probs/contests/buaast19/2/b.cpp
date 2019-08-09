#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=209;
 
int Tn;
 
int n;
int nn;
char s[maxn];
int L[maxn],R[maxn];
int cmp(int t1,int t2){
    int l1=L[t1],r1=R[t1];
    int l2=L[t2],r2=R[t2];
    int mxlen=max(r1-l1+1,r2-l2+1);
    for(int i=1;i<=mxlen;++i){
        if(i+l1-1>r1)return 1;
        if(i+l2-1>r2)return 0;
        if(s[i+l1-1]<s[i+l2-1])return 1;
        if(s[i+l1-1]>s[i+l2-1])return 0;
    }
    return 1;
}
 
void print(int x){
    for(int i=L[x];i<=R[x];++i){
        printf("%c",s[i]);
    }
}
 
int main(){
    scanf("%d",&Tn);
    while(Tn--){
        nn=0;
        scanf("%s",s+1);
        n=strlen(s+1);
        int r=1;
        if(s[1]=='1'){
            while(s[r]=='1')++r;
            nn=1;L[1]=1;R[1]=r-1;
        }
        for(int i=r;i<=n;i=r+1){
            r=i;
            while(s[r+1]=='0')++r;
            while(s[r+1]=='1')++r;
            L[++nn]=i;R[nn]=r;
        }
         
        for(int i=1;i<=nn;){
            int j;
            for(j=i;;++j){
                if(j==nn+1)break;
                if(cmp(i,j)==1){
                    R[i]=R[j];
                    print(j);
                }
                else break;
            }
            i=j;
            printf(" ");
        }
         
        printf("\n");
    }
     
    return 0;
}