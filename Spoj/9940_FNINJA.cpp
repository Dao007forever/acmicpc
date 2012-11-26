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

#define MAXN 1005
const double PI = acos(-1.0);
const double eps = 1e-8;
int sig(double d) {
	return (d > eps) - (d < -eps);
}
struct Point {
	double x, y;

	double dist(const Point &p) {
		return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
	}

	void input() {
		scanf("%lf%lf", &x, &y);
	}
};
struct Circle {
	Point cen;
	double radis;

	bool inside(const Circle &c) {
		double d = cen.dist(c.cen);
		return sig(radis - (d + c.radis)) >= 0;
	}

	bool intersect(const Circle &c) {
		double d = cen.dist(c.cen);
		return sig(d - (radis + c.radis)) <= 0;
	}
}cir[MAXN];
int n, vecnum;
struct node {
	double ang;
	int type;

	node() {}
	node(double ang, int type) : ang(ang), type(type) {}

	bool operator < (const node &p) const {
		if (sig(ang - p.ang) != 0) return sig(ang - p.ang) < 0;
		return type > p.type;
	}
}vec[MAXN << 3];

double change(double ang) {
	while (ang >= 2.0*PI) ang -= 2.0*PI;
	while (ang < 0) ang += 2.0*PI;
	return ang;
}

void addVec(double ang1, double ang2, int &cnt) {
	if (sig(ang1 - ang2) > 0) cnt++;
	vec[vecnum++] = node(ang1, 1);
	vec[vecnum++] = node(ang2, -1);
}

int main(int argc, char const *argv[])
{
	int Test;
	scanf("%d", &Test);
	for (int cas = 1; Test--; cas++) {
		printf("Case #%d: ", cas);
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			cir[i].cen.input();
			scanf("%lf", &cir[i].radis);
		}
		int ret = 0;
		for (int i = 0; i < n; i++) {
			int cnt = 1;
			vecnum = 0;
			for (int j = 0; j < n; j++) {
				if (i == j ) continue;
				double ang = atan2(cir[j].cen.y - cir[i].cen.y, cir[j].cen.x - cir[i].cen.x);
				double d = cir[i].cen.dist(cir[j].cen);
				if (cir[i].inside(cir[j])) continue;
				if (cir[j].inside(cir[i])) {
					cnt++;
					continue;
				} else if (cir[i].intersect(cir[j])) {
					double outer = acos((cir[i].radis - cir[j].radis) / d);
					double angle_outer1 = change(ang - outer), angle_outer2 = change(ang + outer);
					addVec(angle_outer1, angle_outer2, cnt);
				} else {
					double outer = acos((cir[i].radis - cir[j].radis) / d);
					double inner = acos((cir[i].radis + cir[j].radis) / d);
					double angle_outer1 = change(ang - outer), angle_outer2 = change(ang + outer);
					double angle_inner1 = change(ang - inner), angle_inner2 = change(ang + inner);
					//addVec(angle_outer1, angle_inner2, cnt);
					//addVec(angle_inner1, angle_outer2, cnt);
					addVec(angle_outer1, angle_inner1, cnt);
					addVec(angle_inner2, angle_outer2, cnt);
				}
			}
			sort(vec, vec + vecnum);
			ret = max(ret, cnt);
			for (int i = 0; i < vecnum; i++) {
				cnt += vec[i].type;
				ret = max(ret, cnt);
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}