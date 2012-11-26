#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;
const int N=155;
const double pi=acos(-1);
const double eps=1e-8;
struct Point{
       double x,y;
       Point operator >> (double angle){
             Point res;
             res.x=x*cos(angle)+y*sin(angle);
             res.y=y*cos(angle)-x*sin(angle);
             return res;
       }
}a[N];
int n,m1,m2;
double d;

double dis(Point A,Point B){
       return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
}

bool Get(Point Mid){
     Point XL,tmp;
     XL.x=a[m1].x-Mid.x;
     XL.y=a[m1].y-Mid.y;
     double tt=2*pi/n;
     tmp=XL>>(tt*(m2-m1));
     tmp.x+=Mid.x;
     tmp.y+=Mid.y;
     if (fabs(tmp.x-a[m2].x)<eps && fabs(tmp.y-a[m2].y)<eps){
       int i,j=0;
       for (i=m1%n+1;i!=m1;i=i%n+1){
           j++;
           tmp=XL>>(tt*j);
           a[i].x=tmp.x+Mid.x;
           a[i].y=tmp.y+Mid.y;
       }
       for (i=1;i<=n;i++)
         printf("%.6lf %.6lf\n",a[i].x,a[i].y);
       return true;
     }
     else return false;
}

bool Try(){
     Point tmp,Mid;
     Mid.x=(a[m1].x+a[m2].x)/2;
     Mid.y=(a[m1].y+a[m2].y)/2;
     if ((m2-m1)*2==n) return Get(Mid);
     Point XL;
     double k;
     XL.x=a[m2].x-a[m1].x;
     XL.y=a[m2].y-a[m1].y;
     tmp=XL>>(pi/2);
     k=sqrt(d*d/(tmp.x*tmp.x+tmp.y*tmp.y));
     tmp.x*=k;
     tmp.y*=k;
     tmp.x+=Mid.x;
     tmp.y+=Mid.y;
     if (Get(tmp)) return true;
     tmp.x-=Mid.x;
     tmp.y-=Mid.y;
     tmp=tmp>>pi;
     tmp.x+=Mid.x;
     tmp.y+=Mid.y;
     Get(tmp);
}

int main(){
	freopen("a", "r", stdin);
    scanf("%d%d%d",&n,&m1,&m2);
    scanf("%lf%lf%lf%lf",&a[m1].x,&a[m1].y,&a[m2].x,&a[m2].y);
    if (m1>m2) swap(m1,m2);
    double angle=pi/n*(m2-m1);
    while (angle>pi) angle-=pi;
    while (angle<-pi) angle+=pi;
    if ((m2-m1)*2==n) Try();
    else{
      d=dis(a[m1],a[m2])/2/tan(angle);
      Try();
    }
    return 0;  
}
