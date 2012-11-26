/*
 * Author: Yang Zhang
 * Created Time: Tue 28 Aug 2012 07:41:21 PM CST
 * File Name: 3968.cpp
 */
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <bitset>
#include <vector>
#include <cstdio>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;

#define maxn 50005
double my_sqrt(double d) {return sqrt(max(d, 0.0));}
double my_acos(double d) {return acos(d<-1?-1:d>1?1:d);}
#define sqr(v) ((v)*(v))
const double eps = 1E-10;
int sig(double d) {
    return (d>eps) - (d<-eps);
}
struct Point {
    double x, y;
    Point(double x, double y) : x(x), y(y) {}
    Point() {}
    Point operator - (const Point & p) const {
        return Point(x-p.x, y-p.y);
    }
    Point operator + (const Point & p) const {
        return Point(x+p.x, y+p.y);
    }
    double operator * (const Point &b) const {
        return x * b.y - y * b.x;
    }
    bool operator == (const Point & p) const {
        return sig(x-p.x)==0 && sig(y-p.y)==0;
    }
    bool operator < (const Point & p) const {
        return sig(x-p.x)!=0 ? x<p.x : sig(y-p.y)<0;
    }
    Point resize(double d) {
        d /= my_sqrt(sqr(x)+sqr(y));
        return Point(x*d, y*d);
    }
    Point left90() {
        return Point(-y, x);
    }
    Point rotate(double radian) {    //逆时针转
        double c = cos(radian), s = sin(radian);
        return Point(x*c-y*s, y*c+x*s);
    }
    double mod() {
        return my_sqrt(sqr(x)+sqr(y));
    }
    void input() {
        scanf("%lf%lf", &x, &y);
    }
    void output() {
        printf("x = %.2f, y = %.2f\n", x, y);
    }
}p[maxn];
struct hplane {
    Point s,t;
    double ang;
    Point cross (const hplane &b) const {
        double s1 = (b.t-s) * (b.s-s);
        double s2 = (b.s-t) * (b.t-t);
        return Point((s.x*s2+t.x*s1) / (s2+s1), (s.y*s2+t.y*s1) / (s2+s1));
    }
    bool operator < (const hplane &b) const {
        if (sig(b.ang - ang) != 0)
            return ang < b.ang;
        return sig((b.t-b.s)*(t-b.s)) >= 0;
    }
};
hplane Planes[100010],Q[100010];
Point Anss[100010];

void add_hplane(Point s,Point t,int &cnt) {
    Planes[cnt].s = s;
    Planes[cnt].t = t;
    Planes[cnt].ang = atan2(t.y-s.y,t.x-s.x);
    cnt++;
}

bool isright(hplane h, Point p) {
    double num = (p-h.s) * (h.t-h.s);
    return sig(num)>0;
}

int hpi(int cnt) {
    //sort(Planes, Planes + cnt);
    int len = 1 ;
    for (int i = 1; i < cnt; i++)
        if (sig(Planes[i].ang - Planes[i-1].ang) != 0)
            Planes[len++] = Planes[i];
    cnt = len;
    Q[0] = Planes[0];
    Q[1] = Planes[1];
    int l = 0, r = 1;
    for (int i = 2; i < cnt; i++) {
        while (l < r && isright(Planes[i], Q[r].cross(Q[r-1]))) r--;
        while (l < r && isright(Planes[i], Q[l].cross(Q[l+1]))) l++;
        Q[++r] = Planes[i];
    }
    while (l < r && isright(Q[l], Q[r].cross(Q[r-1]))) r--;
    while (l < r && isright(Q[r], Q[l].cross(Q[l+1]))) l++;
    if (r <= l + 1) return 0;
    len = 0;
    for (int i = l; i < r; i++)
        Anss[len++] = Q[i].cross(Q[i+1]);
    Anss[len++] = Q[l].cross(Q[r]);
    int tcnt = 1;
    for (int i = 1; i < len; i++)
        if (!(Anss[i] == Anss[i-1])) Anss[tcnt++] = Anss[i];
    if (tcnt != 1 && Anss[tcnt-1] == Anss[0]) tcnt--;
    return tcnt;
}

Point ps[maxn];
int n;

double area(Point * p, int n) {
    double res = 0;
    p[n] = p[0];
    for(int i = 0; i < n; i ++) {
        res += p[i].x*p[i+1].y - p[i+1].x*p[i].y;
    }
    return res / 2;
}
bool check(int k) {
    if (n - k <= 2) return true;
    int cnt = 0;
    for (int i = 0; i < n; i++)
        add_hplane(ps[i], ps[(i + k + 1) % n], cnt);
    int len = hpi(cnt);
    if (sig(area(Anss, len) == 0)) return true;
    return false;
}
int main() {
    while (~scanf("%d", &n)) {
        for (int i = 0; i < n; i++)
            ps[i].input();
        for (int i = 1; i <= n / 2; i++)
            swap(ps[i], ps[n - i]);
        int l = 0, r = n, ret = 0;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid)) {
                ret = mid;
                r = mid - 1;
            } else l = mid + 1;
        }
        printf("%d\n", ret);
    }
    return 0;
}

