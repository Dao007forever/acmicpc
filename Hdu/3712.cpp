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
#define fi first
#define se second
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;

const double eps = 1e-8;
const double PI = acos(-1.0);
const double inf = 1e50;
int sig(double d) {
	return (d > eps) - (d < -eps);
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
	Point left90() {
		return Point(-y, x);
	}
	Point rotate(double radian) {	//逆时针转
		double c = cos(radian), s = sin(radian);
		return Point(x*c-y*s, y*c+x*s);
	}
	double len() {
		return sqrt(x * x + y * y);
	}
	double dist(const Point &p) {
		return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
	}
	void input() {
		scanf("%lf%lf", &x, &y);
	}
	void output() {
		printf("x = %.2f, y = %.2f\n", x, y);
	}
}prism[5], ps[5], ori, dir;
double nn;
int cas[5];

double cross(const Point & o, const Point & a, const Point & b) {
	return (a.x-o.x)*(b.y-o.y) - (b.x-o.x)*(a.y-o.y);
}

double dot(Point o, Point a, Point b) {
	return (a.x-o.x)*(b.x-o.x) + (a.y-o.y)*(b.y-o.y);
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

int rayCross(Point a, Point b, Point c, Point d, Point &p) {
	int cas = lineCross(a, b, c, d, p);
	if (cas != 1) {
		return cas;
	} else {
		if (sig(dot(a, b, p)) >= 0 && sig(dot(p, c, d)) <= 0) {
			return 1;
		} else {
			return 0;
		}
	}
}

Point newDir(double u, Point a, Point b, Point c, Point d) {
	Point f = (c - d).left90();
	Point v = b - a;
	if (sig(dot(Point(0.0, 0.0), v, f)) < 0) {
		f = Point(-f.x, -f.y);
	}
	double alpha = acos(dot(Point(0.0, 0.0), v, f) / f.len() / v.len());
	double beta = asin(sin(alpha) / u);
	if (sig(cross(Point(0.0, 0.0), v, f)) < 0) {
		return f.rotate(beta);
	} else if (sig(cross(Point(0.0, 0.0), v, f)) > 0){
		return Point(-f.x, -f.y).rotate(PI - beta);
	}
	return f.rotate(beta);
}

double solve() {
	for (int i = 0; i < 3; i++) {
		cas[i] = rayCross(ori, dir, prism[i], prism[(i + 1) % 3], ps[i]);
	}
	if (cas[0] != 1 & cas[1] != 1 && cas[2] != 1) {
		Point pt;
		int ans = lineCross(ori, dir, Point(0.0, 0.0), Point(10.0, 0.0), pt);
		if (ans == 1 && sig(dot(ori, dir, pt)) >= 0) {
			return pt.x;
		} else {
			return inf;
		}
	}
	double dist = inf;
	Point firPs;
	int firCas;
	for (int i = 0; i < 3; i++) {
		if (cas[i] == 1) {
			double tmp = ori.dist(ps[i]);
			if (sig(tmp - dist) < 0) {
				dist = tmp;
				firPs = ps[i];
				firCas = i;
			}
		}
	}
	dir = newDir(nn, ori, dir, prism[firCas], prism[(firCas + 1) % 3]) + firPs;

	Point secPs;
	int secCas;
	for (int i = 0; i < 3; i++) {
		if (firCas == i) continue;
		secCas = rayCross(firPs, dir, prism[i], prism[(i + 1) % 3], secPs);
		if (secCas == 1) {
			secCas = i;
			break;
		}
	}
	dir = newDir(1.0 / nn, firPs, dir, prism[secCas], prism[(secCas + 1) % 3]) + secPs;

	Point pt;
	int ans = lineCross(secPs, dir, Point(0.0, 0.0), Point(10.0, 0.0), pt);
	if (ans == 1 && sig(dot(secPs, dir, pt)) >= 0) {
		return pt.x;
	} else {
		return inf;
	}
}


int main(int argc, char const *argv[])
{
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		ori.input();
		dir.input();
		for (int i = 0; i < 3; i++) {
			prism[i].input();
		}
		scanf("%lf", &nn);
		double ret = solve();
		if (sig(ret - inf) == 0) {
			puts("Error");
		} else {
			printf("%.3f\n", ret);
		}
	}
	return 0;
}