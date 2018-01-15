#include<cstdio>
#include<cstring>
inline void go(int &a,int b){if(a<b)a=b;}
int T,maxP,W,AP[2005],BP[2005],AS[2005],BS[2005],f[2005][2005];
struct ele//单调队列元素
{
    int val,k;
    ele(){}
    ele(int v,int kk):val(v),k(kk){}
};
struct Deque//手写双端队列
{
    ele dat[2005];int s,t;
    ele front(){return dat[s];}
    ele back(){return dat[t-1];}
    bool empty(){return s==t;}
    void push(ele x){dat[t++]=x;}
    void pop_front(){++s;}
    void pop_back(){--t;}
    void clear(){s=t=0;}
}Q;
int DP()
{
    memset(f,192,sizeof(f));
    for(int i=1;i<=T;++i)
    {
        for(int j=0;j<=maxP;++j)//不买
         f[i][j]=f[i-1][j];
        for(int j=0;j<=AS[i];++j)//如果当天是第一次买股票，则不需考虑上次购买时限的限制
         go(f[i][j],-AP[i]*j);
        if(i-W-1<0)continue;
        Q.clear();
        for(int j=0;j<=maxP;++j)//买进股票
     {
            while(!Q.empty() && Q.front().k<j-AS[i])Q.pop_front();
            while(!Q.empty() && Q.back().val<=f[i-W-1][j]+AP[i]*j)Q.pop_back();
            Q.push(ele(f[i-W-1][j]+AP[i]*j,j));
            go(f[i][j],Q.front().val-AP[i]*j);
        }
        Q.clear();
        for(int j=maxP;j>=0;--j)//卖出股票
     {
            while(!Q.empty() && Q.front().k>j+BS[i])Q.pop_front();
            while(!Q.empty() && Q.back().val<=f[i-W-1][j]+BP[i]*j)Q.pop_back();
            Q.push(ele(f[i-W-1][j]+BP[i]*j,j));
            go(f[i][j],Q.front().val-BP[i]*j);
        }
    }
    return f[T][0];
}
int main()
{
    scanf("%d%d%d",&T,&maxP,&W);
    for(int i=1;i<=T;++i)
        scanf("%d%d%d%d",AP+i,BP+i,AS+i,BS+i);
    printf("%d\n",DP());
}
