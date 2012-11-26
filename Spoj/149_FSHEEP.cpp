/*
 * Author : Yang Zhang
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

#define sqr(v) ((v)*(v))
const int maxn = 100005;
const double eps = 1e-8;
const double PI = acos(-1.0);
int sig(double d) {
	return (d>eps) - (d<-eps);
}
double my_sqrt(double d) {return sqrt(max(d, 0.0));}
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
	Point operator * (double d) const {
		return Point(x*d, y*d);
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
	Point rotate(double radian) {	//逆时针转
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
}ps[100005];
int n, m;
double ang[maxn];
double cross(const Point & o, const Point & a, const Point & b) {
	return (a.x-o.x)*(b.y-o.y) - (b.x-o.x)*(a.y-o.y);
}
double dot(Point o, Point a, Point b) {
	return (a.x-o.x)*(b.x-o.x) + (a.y-o.y)*(b.y-o.y);
}
double area(Point * p, int n) {
	double res = 0;
	p[n] = p[0];
	for(int i = 0; i < n; i ++) {
		res += p[i].x*p[i+1].y - p[i+1].x*p[i].y;
	}
	return res / 2;
}
bool onSeg(Point p, Point a, Point b) {
	return sig(cross(p, a, b))==0 && sig(dot(p, a, b))<=0;
}
void init() {
	if(area(ps, n) < 0)	reverse(ps, ps+n);
	rotate(ps, min_element(ps, ps+n), ps+n);
	for(int i = 1; i < n; i ++) {
		ang[i] = atan2(ps[i].y-ps[0].y, ps[i].x-ps[0].x);
	}
	ang[0] = -PI/2;
}
bool dcmp(double a, double b) {
	return sig(a-b) < 0;
}
//0 外 2 内 1 边上
int judge(Point p) {
	if(onSeg(p, ps[0], ps[1]) || onSeg(p, ps[0], ps[n-1]))	return 1;
	int idx = lower_bound(ang, ang+n, atan2(p.y-ps[0].y, p.x-ps[0].x), dcmp) - ang;
	if(idx <= 1 || idx == n)	return 0;	//外面！
	return 1 + sig(cross(ps[idx-1], ps[idx], p));
}

int main() {
	freopen("in", "r", stdin);
	int Test;
	cin >> Test;
	while (Test--) {
		memset(ang, 0, sizeof(ang));
		cin >> n >> m;
		for (int i = 0; i < n; i++)
			ps[i].input();
		init();
		int ret = 0;
		for (int i = 0; i < m; i++) {
			Point p;
			scanf("%lf%lf", &p.x, &p.y);
			if (sig(p.x) == 0 && sig(p.y) == 0) ret++;
			else if (judge(p)) ret++;
		}
		cout << ret << endl;
	}
}
