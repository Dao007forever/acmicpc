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
	void input() {
		scanf("%lf%lf", &x, &y);
	}
	bool operator < (const Point &pt) const {
		if (sig(x - pt.x) != 0) return sig(x - pt.x) < 0;
		return sig(y - pt.y) < 0;
	}
	bool operator == (const Point &pt) const {
		return sig(x - pt.x) == 0 && sig(y - pt.y) == 0;
	}
	bool operator != (const Point &pt) const {
		return sig(x - pt.x) != 0 || sig(y - pt.y) != 0;
	}
	double dist(const Point &pt) {
		return sqrt((x - pt.x) * (x - pt.x) + (y - pt.y) * (y - pt.y));
	}
}ps[20];
double cross(const Point & o, const Point & a, const Point & b) {
	return (a.x-o.x)*(b.y-o.y) - (b.x-o.x)*(a.y-o.y);
}
struct Triangle {
	Point a, b, c;
	int num;
	double ang[5];
	Triangle() {}
	Triangle(Point _a, Point _b, Point _c) {
		a = _a; b = _b; c = _c;
	}

	bool isTriangle() {
		if (sig(cross(a, b, c)) == 0) return false;
		//if (a == b || b == c || a == c) return false;
		return true;
	}

	double calc(double l1, double l2, double l3) {
		double t = l1 * l1 + l2 * l2 - l3 * l3;
		return acos(t / (2 * l1 * l2));
	}

	void getAngle() {
		double lenA = a.dist(b), lenB = b.dist(c), lenC = c.dist(a);
		num = 0;
		ang[num++] = calc(lenA, lenB, lenC);
		ang[num++] = calc(lenB, lenC, lenA);
		ang[num++] = calc(lenC, lenA, lenB);
		sort(ang, ang + num);
	}

	bool similar(Triangle pt) {
		for (int i = 0; i < 3; i++)
			if (sig(ang[i] - pt.ang[i]) != 0) return false;
		return true;
	}

	void output() {
		printf("%.2f %.2f %.2f %.2f %.2f %.2f\n", a.x, a.y, b.x, b.y, c.x, c.y);
	}
};

int main(int argc, char const *argv[])
{
	int n;
	while (scanf("%d", &n) && n) {
		for (int i = 0; i < n; i++)
			ps[i].input();
		sort(ps, ps + n);
		/*int m = 1;
		for (int i = 1; i < n; i++)
			if (ps[i] != ps[i - 1])
				ps[m++] = ps[i];
		n = m;*/
		n = unique(ps, ps + n) - ps;
		int ret = 0;
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++)
				for (int k = j + 1 ; k < n; k++) {
					Triangle cur = Triangle(ps[i], ps[j], ps[k]);
					cur.getAngle();
					if (!cur.isTriangle()) continue;
					int cnt = 0;
					for (int a = 0; a < n; a++)
						for (int b = a + 1; b < n; b++)
							for (int c = b + 1; c < n; c++) {
								Triangle temp = Triangle(ps[a], ps[b], ps[c]);
								temp.getAngle();
								if (!temp.isTriangle()) continue;
								if (cur.similar(temp)) {
									//cur.output(); temp.output();
									//puts("");
									cnt++;
								}
							}
					ret = max(ret, cnt);
				}
		printf("%d\n", ret);
	}
	return 0;
}