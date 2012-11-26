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

const double eps = 1e-8;
int sig(double d) {
	return (d > eps) - (d < -eps);
}
struct Point {
	double x, y;

	Point (double x, double y) : x(x), y(y) {}
	
	Point() {}

	Point operator - (const Point &p) const {
		return Point(x - p.x, y - p.y);
	}

	Point operator + (const Point &p) const {
		return Point(x + p.x, y + p.y);
	}

	Point operator * (double d) const {
		return Point(x * d, y * d);
	}

	bool operator != (const Point &p) {
		return sig(x - p.x) != 0 || sig(y - p.y) != 0;
	}

	bool operator < (const Point &p) {
		return sig(x - p.x) != 0 ? x < p.x : sig(y - p.y) < 0;
	}

	Point left90() {
		return Point(-y, x);
	}

	void input() {
		scanf("%lf %lf", &x, &y);
	}
}A, B, C;
double L;

double dis(Point a, Point b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double cross(Point o, Point a, Point b) {
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

double dot(Point o, Point a, Point b) {
	return (a.x - o.x) * (b.x - o.x) + (a.y - o.y) * (b.y - o.y);
}

double pointToLine(Point o, Point a, Point b) {
	double d = dis(a, b);
	double s = cross(a, b, o) / d;
	return fabs(s);
}

int main() {
	A.input();
	B.input();
	C.input();
	scanf("%lf", &L);
	double r1 = min(dis(A, C), dis(B, C));
	if (A != B) {
		if (dot(A, B, C) > 0 && dot(B, A, C) > 0)
			r1 = min(r1, pointToLine(C, A, B));
	}
	double r2 = max(dis(A, C), dis(B, C));
	r1 -= L;
	r2 -= L;
	if (sig(r1) < 0) r1 = 0.0;
	if (sig(r2) < 0) r2 = 0.0;
	printf("%.2f\n%.2f\n", r1, r2);
	return 0;
}
