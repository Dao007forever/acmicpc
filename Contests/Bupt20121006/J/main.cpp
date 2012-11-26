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
int sig(double d) {
	return (d > eps) - (d < -eps);
}
struct Point {
	double x, y;
	Point() {}
	Point(double x, double y) : x(x), y(y) {}
	bool operator != (const Point &pt) const {
		return sig(x - pt.x) != 0 || sig(y - pt.y) != 0;
	}
	void input() {
		scanf("%lf%lf", &x, &y);
	}
}ps[105];
int n, cnt1, cnt2, cnt3;
double vx, vy, g;

double cross(const Point & o, const Point & a, const Point & b) {
	return (a.x-o.x)*(b.y-o.y) - (b.x-o.x)*(a.y-o.y);
}

double dot(Point o, Point a, Point b) {
	return (a.x-o.x)*(b.x-o.x) + (a.y-o.y)*(b.y-o.y);
}

bool onSeg(Point p, Point a, Point b) {
	return sig(cross(p, a, b))==0 && sig(dot(p, a, b))<=0;
}

double calc(double x) {
	double a = -g / 2.0 / (vx * vx), b = vy / vx;
	return a * x * x + b * x;
}

void solve(const Point &pa, const Point &pb) {
	if (sig(pa.x - pb.x) == 0) {
		double y = calc(pa.x);
		Point v = Point(pa.x, y);
		if (onSeg(v, pa, pb) && v != pa && v != pb) cnt1++;
	} else {
		double k = (pa.y - pb.y) / (pa.x - pb.x);
		double a = g / 2.0 / (vx * vx);
		double b = k - vy / vx;
		double c = pa.y - k * pa.x;
		double delta = b * b - 4 * a * c;
		if (sig(delta) == 0) {
			double x = -b / 2 / a;
			double y = calc(x);
			Point v = Point(x, y);
			if (onSeg(v, pa, pb) && v != pa && v != pb) cnt3++;
		} else if (sig(delta)) {
			double x = (-b + sqrt(delta)) / 2 / a;
			double y = calc(x);
			Point v = Point(x, y);
			if (onSeg(v, pa, pb) && v != pa && v != pb) cnt1++;
			x = (-b - sqrt(delta)) / 2 / a;
			y = calc(x);
			v = Point(x, y);
			if (onSeg(v, pa, pb) && v != pa && v != pb) cnt1++;
		}
	}
}

int main(int argc, char const *argv[])
{
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d%lf%lf%lf", &n, &vx, &vy, &g);
		for (int i = 0; i < n; i++)
			ps[i].input();
		ps[n] = ps[0];
		cnt1 = 0; cnt2 = 0; cnt3 = 0;
		for (int i = 0; i < n; i++)
			solve(ps[i], ps[i + 1]);
		for (int i = 0; i < n; i++) {
			double y = calc(ps[i].x);
			if (sig(y - ps[i].y) == 0) cnt2++;
		}
		int ret = cnt1 + cnt2 + cnt3;
		bool flag = false;
		for (int i = 0; i < n; i++) {
			double y = calc(ps[i].x);
			if (sig(ps[i].y - y) > 0) flag = true;
		}
		if (cnt1) {
			puts("INF");
		} else if (cnt2 >= 2 && flag) {
			puts("INF");
		} else {
			printf("%d\n", cnt1 + cnt2 + cnt3);
		}
	}
	return 0;
}