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

#define sqr(v) ((v)*(v))
const double eps = 1e-8;
int sig(double d) {
	return (d>eps) - (d<-eps);
}
double my_sqrt(double d) {return sqrt(max(d, 0.0));}
struct Point {
	double x, y;
	Point() {}
	Point(double x, double y) : x(x), y(y) {}
	void input() {
		scanf("%lf%lf", &x, &y);
	}
}ps[155];
double dis(Point a, Point b) {
	return my_sqrt(sqr(a.x-b.x) + sqr(a.y-b.y));
}
double cross(const Point & o, const Point & a, const Point & b) {
	return (a.x-o.x)*(b.y-o.y) - (b.x-o.x)*(a.y-o.y);
}
double pointToLine(Point o, Point a, Point b) {
	double d = dis(a, b);
	double s = cross(a, b, o) / d;
	return fabs(s);
}
struct Circle {
	double r;
	Point cen;
	Circle() {}
	Circle(Point cen, double r) {
		this->cen = cen;
		this->r = r;
	}
	bool inter(const Point &a, const Point &b) {
		double d = pointToLine(cen, a, b);
		if (sig(d - r) <= 0) {
			if (sig(dis(cen, a) - r) <= 0) return true;
			if (sig(dis(cen, b) - r) <= 0) return true;
			double ang = ( sqr(dis(cen, a)) + sqr(dis(cen, b)) - sqr(dis(a, b)) ) / 2.0 / dis(cen, a) / dis(cen, b);
			if (sig(ang) <= 0) return true;
		}
		return false;
	}
}c[105];
int n, g;
double r;
int f[155][155];
bool v[155][155];

bool check(int a, int b) {
	for (int i = 0; i < g; i++) {
		if (c[i].inter(ps[a], ps[b])) return false;
	}
	return true;
}

int main(int argc, char const *argv[])
{
	scanf("%d%d%lf", &n, &g, &r);
	for (int i = 0; i < n; i++) {
		ps[i].input();
	}
	for (int i = 0; i < g; i++) {
		double x, y;
		scanf("%lf%lf", &x, &y);
		c[i] = Circle(Point(x, y), r);
	}
	memset(f, 0, sizeof(f));
	memset(v, 0, sizeof(v));
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (abs(i - j) == 1 || abs(i - j) == n - 1) continue;
			// printf("%d %d ", i + 1, j + 1);
			v[i][j] = v[j][i] = check(i, j);
/*			if (v[i][j]) {
				puts("true");
			} else puts("false");*/
		}
	}
	for (int l = 2; l < n; l++)
		for (int i = 0; i < n; i++) {
			int j = i + l;
			for (int k = i + 1; k < j; k++)
				f[i][j % n] = max(f[i][j % n], f[i][k % n] + f[k % n][j % n]);
			f[i][j % n] += v[i][j % n];
		}
	int ret = f[0][n - 1];
	for (int i = 1; i < n; i++)
		ret = max(ret, f[i][i - 1]);
	printf("%d\n", ret);
	return 0;
}