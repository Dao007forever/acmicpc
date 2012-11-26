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

const double eps = 1e-8;
const double R = 1.0;
const double PI = acos(-1.0);
int sig(double d) {
	return (d > eps) - (d < -eps);
}
struct Point {
	double x, y;

	double dist(const Point &pt) {
		return sqrt((x - pt.x) * (x - pt.x) + (y - pt.y) * (y - pt.y));
	}
}ps[305];
struct node {
	double ang;
	int flag;
	node() {}
	node(double ang, int flag) : ang(ang), flag(flag) {}
	bool operator < (const node &pt) const {
		if (sig(ang - pt.ang) != 0) return sig(ang - pt.ang) < 0;
		return flag < pt.flag;
	}
}vec[1205];
int n;

double fit(double angle) {
	if (sig(angle) < 0) return angle += 2.0 * PI;
	if (sig(angle - 2.0 * PI) > 0) return angle -= 2.0 * PI;
	return angle;
}

void work() {
	int ret = 0;
	for (int i = 0; i < n; i++) {
		int len = 0;
		//vector<pair<double, int> > vec;
		for (int j = 0; j < n; j++) {
			if (i == j) continue;
			double d = ps[i].dist(ps[j]) / 2.0;
			if (sig(d - R) > 0) continue;
			double alpha = fit(atan2(ps[j].y - ps[i].y, ps[j].x - ps[i].x));
			double theta = acos(d / R);
			double ang1 = fit(alpha - theta);
			double ang2 = fit(alpha + theta);

			if (sig(ang1 - ang2) > 0) {
				vec[len++] = node(0, 0);
				vec[len++] = node(ang2, 1);
				vec[len++] = node(ang1, 0);
				vec[len++] = node(2.0 * PI, 1);
				//vec.PB(MP(0, 0));
				//vec.PB(MP(ang2, 1));
				//vec.PB(MP(ang1, 0));
				//vec.PB(MP(2.0 * PI, 1));
			} else {
				vec[len++] = node(ang1, 0);
				vec[len++] = node(ang2, 1);
				//vec.PB(MP(ang1, 0));
				//vec.PB(MP(ang2, 1));
			}

		}
		//sort(vec.begin(), vec.end());
		sort(vec, vec + len);
		int cnt = 0, Max = 0;
		//for (vector<pair<double, int> >::iterator it = vec.begin(); it != vec.end(); it++) {
		for (int i = 0; i < len; i++) {
			//if (it->second == 0) cnt++;
			if (vec[i].flag == 0) cnt++;
			else cnt--;
			Max = max(Max, cnt);
		}
		ret = max(ret, Max + 1);
	}
	printf("%d\n", ret);
}

int main(int argc, char const *argv[])
{
	while (~scanf("%d", &n) && n) {
		for (int i = 0; i < n; i++)
			scanf("%lf%lf", &ps[i].x, &ps[i].y);
		work();
	}
	return 0;
}