#include<bits/stdc++.h>

#define N 10101

#define db double

#define re(x,n) memset(x,0,sizeof(x[0])*n)

using namespace std;

db A,B,C,L,R,D;//二次函数

db f[N],b[N];//一次函数

db xx[N],y[N];

db l[N];

int main(){

    int T;

    cin>>T;

    while(T--)

    {

        int n;

        cin>>n;

        int i;

        for(i=0;i<n;i++){

            cin>>xx[i]>>y[i];

            if(i){

                l[i]=sqrt((xx[i]-xx[i-1])*(xx[i]-xx[i-1])+(y[i]-y[i-1])*(y[i]-y[i-1]));

            }

        }

        l[n]=sqrt((xx[n-1]-xx[0])*(xx[n-1]-xx[0])+(y[n-1]-y[0])*(y[n-1]-y[0]));

        f[1]=1,b[1]=0;

        for(i=2;i<=n;i++){

            f[i]=-1*f[i-1];

            b[i]=l[i-1]-b[i-1];

        }

        L=-1e9;

        R=1e9;

        for(i=1;i<=n;i++){

            A+=1.0;

            B+=2.0*f[i]*b[i];

            C+=b[i]*b[i];

            if(f[i]>0)L=max(L,-1*b[i]);

            else R=min(R,b[i]);

        }

        D=-1.0*B/(2.0*A);

        db x;

        if(L>R+1e-5){

            //cout<<'A'<<endl;

            cout<<"IMPOSSIBLE"<<endl;

            continue;

        }

        if(f[n]>0){

            x=(l[n]-b[n])/2;

            if(x>=L-1e-6&&x<=R+1e-6);//精度

            else {

                //cout<<'B'<<endl;

                cout<<"IMPOSSIBLE"<<endl;

                continue;

            }

        }

        else {

            if(fabs(b[n]-l[n])<1e-5){

                x=D;

                if(D<L){x=L;}

                if(D>R){x=R;}

            }

            else {

                //cout<<'C'<<endl;

                cout<<"IMPOSSIBLE"<<endl;

                continue;

            }

        }

        //printf("%f %f %f %f\n",L,R,D,x);

        printf("%.2f\n",(A*x*x+B*x+C)*acos(-1));

        for(i=1;i<=n;i++){

            printf("%.2f\n",max(0.0,f[i]*x+b[i]));

        }

        A=B=C=D=L=R=0;

        re(f,n+10);

        re(b,n+10);

        //re(xx,n+1);

        re(y,n+10);

        re(l,n+10);

    }

}

/*

3

4

0 0

11 0

27 12

5 12



5

0 0

7 0

7 3

3 6

0 6



5

0 0

1 0

6 12

3 16

0 12

*/
