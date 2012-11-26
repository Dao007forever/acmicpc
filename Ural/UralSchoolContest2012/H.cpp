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

double my_sqrt(double d) {return sqrt(max(d, 0.0));}
double my_acos(double d) {return acos(d<-1?-1:d>1?1:d);}
#define sqr(v) ((v)*(v))
const double eps = 1E-6;
const double PI = acos(-1.0);
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
	void output() {
		printf("x = %.2f, y = %.2f\n", x, y);
	}
}ori[5], ps[5];

struct Line {
	Point a, b;
}line[5];
double cross(const Point & o, const Point & a, const Point & b) {
	return (a.x-o.x)*(b.y-o.y) - (b.x-o.x)*(a.y-o.y);
}
int lineCross(Point a, Point b, Point c, Point d, Point &p) {
	double s1, s2;
	s1=cross(a,b,c);
	s2=cross(a,b,d);
	if(sig(s1)==0 && sig(s2)==0)	return 2;
	if(sig(s2-s1)==0)	return 0;
	p.x = (c.x*s2-d.x*s1)/(s2-s1);
	p.y = (c.y*s2-d.y*s1)/(s2-s1); 
	return 1;
}
double dist(const Point &a, const Point &b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
double area(const Point &a, const Point &b, const Point &c) {
	double lenA = dist(a, b), lenB = dist(b, c), lenC = dist(c, a);
	double p = (lenA + lenB + lenC) / 2.0;
	return sqrt(p * (p - lenA) * (p - lenB) * (p - lenC));
}
bool parallel(Line const &A, Line const &B) {
	double k1 = atan2(A.a.x - A.b.x, A.a.y - A.b.y);
	double k2 = atan2(B.a.x - B.b.x, B.a.y - B.b.y);
	return sig(k1 - k2) == 0;
}
bool intersect(Point *p) {
	Point a = ori[0], b = ori[0] + (ori[1] - ori[0]).left90();
	Point pt;
	if (lineCross(a, b, ori[2], ori[3], pt) == 1) return true;
	a = ori[1], b = ori[1] + (ori[0] - ori[1]).left90();
	if (lineCross(a, b, ori[2], ori[3], pt) == 1) return true;
	return false;
}
int main(int argc, char const *argv[])
{
	for (int i = 0; i < 4; i++)
		cin >> ori[i].x >> ori[i].y;
	if (ori[1] < ori[0]) swap(ori[0], ori[1]);
	if (ori[3] < ori[2]) swap(ori[2], ori[3]);
	Line A, B;
	A.a = ori[0], A.b = ori[1];
	B.a = ori[2], B.b = ori[3];
	if (parallel(A, B)) {
		if (intersect(ori)) puts("-1");
		else puts("0.000000");
		return 0;
	}
	for (int i = 0; i < 4; i += 2) {
		Point a = ori[i], b = ori[i + 1];
		line[i].a = a; line[i].b = a + (b - a).left90();

		line[i+1].a = b; line[i+1].b = b + (a - b).left90();
	}

	lineCross(line[0].a, line[0].b, line[2].a, line[2].b, ps[0]);
	lineCross(line[0].a, line[0].b, line[3].a, line[3].b, ps[1]);
	lineCross(line[1].a, line[1].b, line[2].a, line[2].b, ps[2]);
	lineCross(line[1].a, line[1].b, line[3].a, line[3].b, ps[3]);
	double ret = area(ps[0], ps[1], ps[2]) + area(ps[1], ps[2], ps[3]);
	printf("%.6f\n", ret);
	return 0;
}