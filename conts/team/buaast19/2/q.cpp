#include<bits/stdc++.h>
const int maxn = 50;
typedef long long ll;
using namespace std;
 
typedef pair<int,int> P;
char s[205];
int nxt[205];
set<P> S;
void init(){
    for(int i = 0, pre = 0; ; i++){
        if(s[i+1]){
            if(s[i] == '1' && s[i+1] == '0'){
                nxt[pre] = i;
                pre = i+1;
            }
        }else{
            nxt[pre] = i;
            nxt[i+1] = -1;
            break;
        }
    }
}
bool check(int l1, int r1, int l2, int r2){
    for(int i = l1, j = l2; i < r2; i++, j++){
        if(j > r2) j = l1;
        if(s[i] > s[j]) return false;
        if(s[i] < s[j]) return true;
    }
    return true;
}
int main(){
    int T; scanf("%d",&T);
    while(T--){
        scanf("%s", s);
        init();
        bool flag = true;
        while(flag){
            flag = false;
            for(int p = 0; nxt[nxt[p]+1] != -1; ){
                if(check(p, nxt[p], nxt[p]+1, nxt[nxt[p]+1])){
                    nxt[p] = nxt[nxt[p]+1];
                    flag = true;
                }else p = nxt[p]+1;
            }
        }
//        int cnt = 0;
        for(int p = 0; nxt[p] != -1; p = nxt[p]+1){
            for(int i = p; i <= nxt[p]; i++) putchar(s[i]);
            putchar(' ');
//            cnt++;
        }
//        printf("%d\n", cnt);
        putchar('\n');
    }
    return 0;
}
