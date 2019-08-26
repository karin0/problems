#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;


double Rm,R,r,x0,yy0,vx,vy;

void calc(double a,double b,double c,double &g,double &mid,double &delt){
    delt=b*b-4*a*c;
    if(delt<=0)return;
    mid=-b/(2*a);
    g=(-b-sqrt(delt))/(2*a);
}


int main(){
    while(scanf("%lf%lf%lf%lf%lf%lf%lf",&Rm,&R,&r,&x0,&yy0,&vx,&vy)!=EOF){
        double delt1,g1,mid1;
        double delt2,g2,mid2;//相离 
        double delt3,g3,mid3;//碰撞
        double a=vx*vx+vy*vy;
        double b=(x0*vx+yy0*vy)*2;
        calc(a,b,x0*x0+yy0*yy0-(R+r)*(R+r),g1,mid1,delt1);
        calc(a,b,x0*x0+yy0*yy0-(R-r)*(R-r),g2,mid2,delt2);
        calc(a,b,x0*x0+yy0*yy0-(Rm+r)*(Rm+r),g3,mid3,delt3);
        
        if(delt1<=0){
            printf("%.6f\n",0.0);
        }else{
            if(delt3<=0){
                printf("%.6f\n",(mid1-g1)*2);
//              if(delt2<=0){
//                  printf("%.6f\n",(mid1-g1)*2);
//              }else{
//                  printf("%.6f\n",(g2-g1)*2);
//              }
            }else{
                printf("%.6f\n",(g3-g1)*2);
//              if(delt2<=0){
//                  printf("%.6f\n",(g3-g1)*2);
//              }else{
//                  printf("%.6f\n",(g2-g1)*2);
//              }
            }
        }
    }
    return 0;
}