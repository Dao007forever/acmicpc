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

const double PI = acos(-1.0);
const double eps = 1e-8;
int sig(double d) {
	return (d > eps) - (d < -eps);
}
struct Point {
	double x, y;
	double ang;
	Point() {}
	Point(double x, double y) : x(x), y(y) {}
	void input() {
		scanf("%lf%lf", &x, &y);	
	}
	void getAngle(const Point &o) {
		ang = atan2(y - o.y, x - o.x);
		if (sig(ang) < 0) ang += 2.0 * PI;
	}
	bool operator < (const Point &p) const {
		return sig(ang - p.ang) < 0;
	}
}ps[1005], pt[1005];

double dist(const Point &a, const Point &b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double calc(const Point &a, const Point &b, const Point &o) {
	double l1 = dist(o, a), l2 = dist(o, b);
	double l3 = dist(a, b);
	return (l1 * l1 + l2 * l2 - l3 * l3 ) / 2.0 / l1 / l2;
}

int main(int argc, char const *argv[])
{
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		int K, n;
		scanf("%d", &K);
		n = 4 * K + 5;
		for (int i = 0; i < n; i++) {
			ps[i].input();
		}
		double ret = 1e50;
		for (int i = 0; i < n; i++) {
			Point ori = ps[i];
			int m = 0;
			for (int j = 0; j < n; j++) {
				if (i == j) continue;
				pt[m] = ps[j];
				pt[m].getAngle(ori);
				m++;
			}
			sort(pt, pt + m);

			for (int i = 0; i < m; i++) {
				pt[m + i] = pt[i];
			}

			int u = 0, v = u + K + 1, w = v + K + 1, z = w + K + 1;
			for (; u < m && z < 2*m; u++, v++, w++, z++) {
				double sum = 0;

				double tmp = calc(pt[u], pt[v], ori);
				double ang = pt[v].ang - pt[u].ang;
				if (sig(ang) < 0) ang += 2.0 * PI;
				if (sig(ang - PI) >= 0) continue;
				sum += abs(tmp) / sqrt(1.0 - tmp * tmp);

				ang = pt[w].ang - pt[v].ang;
				if (sig(ang) < 0) ang += 2.0 * PI;
				if (sig(ang - PI) >= 0) continue;
				tmp = calc(pt[v], pt[w], ori);
				sum += abs(tmp) / sqrt(1.0 - tmp * tmp);

				ang = pt[z].ang - pt[w].ang;
				if (sig(ang) < 0) ang += 2.0 * PI;
				if (sig(ang - PI) >= 0) continue;
				tmp = calc(pt[w], pt[z], ori);
				sum += abs(tmp) / sqrt(1.0 - tmp * tmp);

				ang = pt[u].ang - pt[z].ang;
				if (sig(ang) < 0) ang += 2.0 * PI;
				if (sig(ang - PI) >= 0) continue;
				tmp = calc(pt[z], pt[u], ori);
				sum += abs(tmp) / sqrt(1.0 - tmp * tmp);

				if (sig(sum - ret) < 0) {
					ret = sum;
				}
			}
		}
		if (sig(ret - 1e50) == 0) {
			puts("Impossible");
		} else {
			printf("%.6f\n", ret);
		}
	}
	return 0;
}