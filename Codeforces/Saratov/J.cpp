#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
using namespace std;

double ansD;
int ansI, ansJ;

#define maxn 100010

const double eps = 1E-8;
int sig(double d) {
        return (d>eps) - (d<-eps);
}
struct Point {
        double x, y;
        int idx;
};
double dis(Point a, Point b) {
        return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
int cmp_x(Point a, Point b) {
        return a.x < b.x;
}
int cmp_y(Point a, Point b) {
        return a.y < b.y;
}

double close0(Point * ps, int l, int r) {
        static Point psy[maxn];
        if(r-l <= 1) {
                return 1E300;
        }
        int m = (l+r) / 2;
        double midX = ps[m].x;
        double res = min(close0(ps,l,m), close0(ps,m,r));
        inplace_merge(ps+l, ps+m, ps+r, cmp_y);
        double x1 = midX-res, x2=midX+res;
        int len = 0;
        for(int i = l; i < r; i ++)
                if(sig(x1-ps[i].x)<0 && sig(ps[i].x-x2)<0)
                        psy[len ++] = ps[i];
        for(int i = 0; i < len; i ++)
                for(int j =i+1; j<len && psy[j].y<psy[i].y+res; j ++) {
                        double tmp = dis(psy[i], psy[j]);
                        if(tmp < res) {
                                res = tmp;
                                if(res < ansD) {
                                        ansD = res;
                                        ansI = psy[i].idx;
                                        ansJ = psy[j].idx;
                                }
                        }
                }
        return res;
}
double close(Point * ps, int n) {
        sort(ps, ps+n, cmp_x);
        ansD = 1E300;
        return close0(ps, 0, n);
}
///////////////////////
Point ps[maxn];
int n;
Point ps2[maxn];

int main() {
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
        scanf("%d", &n);
        for(int i = 0; i < n; i ++) {
                scanf("%lf%lf", &ps[i].x, &ps[i].y);
                ps[i].idx = i;
        }
        copy(ps, ps+n, ps2);
        for(int i = 0; i < n; i ++) {
                ps2[i].x = fabs(ps2[i].x);
                ps2[i].y = fabs(ps2[i].y);
        }
        double ans = close(ps2, n);
        /*cout << "ans = " << ans << endl;
        
        cout << ansI << " " << ansJ << endl;
        
        cout << ansD << endl;*/
        
        int k1, k2;
        
        if(sig(ps[ansI].x) > 0) {
                if(sig(ps[ansI].y) > 0) {
                        k1 = 1;
                } else {
                        k1 = 3;
                }
        } else {
                if(sig(ps[ansI].y) > 0) {
                        k1 = 2;
                } else {
                        k1 = 4;
                }
        }
        
        if(sig(ps[ansJ].x) > 0) {
                if(sig(ps[ansJ].y) > 0) {
                        k2 = 4;
                } else {
                        k2 = 2;
                }
        } else {
                if(sig(ps[ansJ].y) > 0) {
                        k2 = 3;
                } else {
                        k2 = 1;
                }
        }
        
        printf("%d %d %d %d\n", ansI+1, k1, ansJ+1, k2);
        
        return 0;
}
