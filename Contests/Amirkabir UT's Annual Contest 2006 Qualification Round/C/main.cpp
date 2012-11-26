/*
 * Author: Yang Zhang
 * Created Time: Fri 29 Jun 2012 08:26:54 PM UTC
 * File Name: main.cpp
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
int sig(double d) {
	return (d > eps) - (d < -eps);
}
struct Point {
	double x, y;

	bool operator == (const Point &p) const {
		return sig(x - p.x) == 0 && sig(y - p.y) == 0;
	}

	bool operator < (const Point &p) const {
		return sig(x - p.x) != 0 ? x < p.x : sig(y - p.y) < 0;
	}

	void input() {
		scanf("%lf %lf", &x, &y);
	}
}ps[111];

double cross(Point o, Point a, Point b) {
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

int graham(Point*p, int n, int*ch) {
#define push(x)     ch[len ++]=x
#define pop()		len --
	sort(p, p+n);
	int len = 0, len0 = 1, i;
	for(i = 0; i < n; i ++) {
		while(len > len0 && sig(cross(p[ch[len-1]], p[ch[len-2]], p[i]))<=0)
			pop();
		push(i);
	}
	len0 = len;
	for(i = n-2; i >= 0; i --) {
		while(len > len0 && sig(cross(p[ch[len-1]], p[ch[len-2]], p[i]))<=0)
			pop();
		push(i);
	}
	return len-1;
}

int initL, n, m;
int id[111];

double caldist(Point a, Point b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main() {
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d%d", &initL, &n);
		for (int i = 0; i < n; i++)
			ps[i].input();
		m = graham(ps, n, id);
		double ret = 0;
		for (int i = 0; i < m; i++)
			ret += caldist(ps[id[i]], ps[id[(i + 1) % m]]);
		if (sig(ret - initL) >= 0) printf("%.5f\n", ret);
		else printf("%.5f\n", (double)initL);
	}
	return 0;
}

