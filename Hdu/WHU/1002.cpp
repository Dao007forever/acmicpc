/*
 * Author : Yang Zhang
 */
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

const double eps = 1e-6;
struct Point {
	int x, y;
}cen, p[111];
int N;
double f[111][2];
int x[111][2], y[111][2];
int xo, yo;

int sig(double d) {
	return (d > eps) - (d < -eps);
}

double dist(Point a, Point b) {
	double dx = (double)(a.x - b.x);
	double dy = (double)(a.y - b.y);
	return sqrt(dx * dx + dy * dy);
}

int main() {
	freopen("in", "r", stdin);
	int Test;
	scanf("%d", &Test);
	for (int cas = 1; cas <= Test; cas++) {
		printf("Case %d: ", cas);
		scanf("%d%d%d", &N, &cen.x, &cen.y);
		memset(f, 0, sizeof(f));
		Point ori;
		ori.x = 0, ori.y = 0;
		for (int i = 1; i <= N; i++) {
			scanf("%d%d", &p[i].x, &p[i].y);
		}
		f[0][0] = f[0][1] = dist(ori, cen);
		x[0][0] = x[0][1] = 0;
		y[0][0] = y[0][1] = 0;
		for (int i = 1; i <= N; i++) {
			Point s;
			s.x = x[i - 1][0] + p[i].x;
			s.y = y[i - 1][0] + p[i].y;
			double d = dist(s, cen);
			if (sig(d - f[i][0]) >= 0) {
				f[i][0] = d;
				x[i][0] = s.x; y[i][0] = s.y;
			}

			s.x = x[i - 1][1] + p[i].x;
			s.y = y[i - 1][1] + p[i].y;
			d = dist(s, cen);
			if (sig(d - f[i][0]) >= 0) {
				f[i][0] = d;
				x[i][0] = s.x; y[i][0] = s.y;
			}

			s.x = x[i - 1][0] - p[i].x;
			s.y = y[i - 1][0] - p[i].y;
			d = dist(s, cen);
			if (sig(d - f[i][1]) >= 0) {
				f[i][1] = d;
				x[i][1] = s.x; y[i][1] = s.y;
			}

			s.x = x[i - 1][1] - p[i].x;
			s.y = y[i - 1][1] - p[i].y;
			d = dist(s, cen);
			if (sig(d - f[i][1]) >= 0) {
				f[i][1] = d;
				x[i][1] = s.x; y[i][1] = s.y;
			}
		}
		double ret = max(f[N][0], f[N][1]);
		printf("%.3f\n", ret);
	}
	return 0;
}
