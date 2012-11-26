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

#define MAXN 300005
const double eps = 1e-15;
int sig(double d) {
	return (d > eps) - (d < -eps);
}
struct Point {
	double x, y;
	bool operator < (const Point &p) const {
		return sig(x - p.x) != 0 ? x < p.x : sig(y - p.y) < 0;
	}
}ps[MAXN];
double ang[MAXN];
int n;

double cross(const Point &o, const Point &a, const Point &b) {
	return (a.x - o.x) * (b.y - o.y) - (b.x - o.x) * (a.y - o.y);
}

double dot(Point o, Point a, Point b) {
	return (a.x - o.x) * (b.x - o.x) + (a.y - o.y) * (b.y - o.y);
}

double area(Point *p, int n) {
	double res = 0;
	p[n] = p[0];
	for (int i = 0; i < n; i++) {
		res += p[i].x * p[i + 1].y - p[i + 1].x * p[i].y;
	}
	return res / 2;
}

void init() {
	if (area(ps, n) < 0) reverse(ps, ps + n);
	rotate(ps, min_element(ps, ps + n), ps + n);
	for (int i = 1; i < n; i++) {
		ang[i] = atan2(ps[i].y - ps[0].y, ps[i].x - ps[0].x);
	}
	ang[0] = -M_PI / 2;
}

bool onSeg(Point p, Point a, Point b) {
	return sig(cross(p, a, b)) == 0 && sig(dot(p, a, b)) <= 0;
}

bool dcmp(double a, double b) {
	return sig(a - b) < 0;
}

// 0:outside; 2:inside; 1:on the edge.
int isinPolygon(Point p) {
	if (onSeg(p, ps[0], ps[1]) || (onSeg(p, ps[0], ps[n - 1]))) return 1;
	int idx = lower_bound(ang, ang + n, atan2(p.y - ps[0].y, p.x - ps[0].x), dcmp) - ang;
	if (idx <= 1 || idx == n) return 0;
	return 1 + sig(cross(ps[idx - 1], ps[idx], p));
}

int main() {
	freopen("in", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%lf%lf", &ps[i].x, &ps[i].y);
	}
	init();
	bool flag = true;
	int m;
	scanf("%d", &m);
	while (m--) {
		Point tmp;
		scanf("%lf%lf", &tmp.x, &tmp.y);
		if (isinPolygon(tmp) == 2) continue;
		else flag = false;
	}
	if (flag) cout << "YES" << endl;
	else cout << "NO" << endl;
	return 0;
}
