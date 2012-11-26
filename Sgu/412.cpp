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

#define MAXN 100005
const double eps = 1e-12;
const double PI = acos(-1.0);
int sig(double d) {
	return (d > eps) - (d < -eps);
}
struct Point {
	double x, y, ang;
	Point() {}
	Point(double x, double y) : x(x), y(y) {}
	void input() {
		scanf("%lf%lf", &x, &y);
	}
	void getAngle() {
		ang = atan2(y, x);
	}
	Point operator - (const Point &pt) const {
		return Point(x - pt.x, y - pt.y);
	}
	double len() {
		return sqrt(x * x + y * y);
	}
	bool operator < (const Point &pt) const {
		return x < pt.x;
	}

}ps[MAXN];
int n, m;
double sum[MAXN];
vector<pair<double, double> > vec;

double cross(const Point & o, const Point & a, const Point & b) {
	return (a.x-o.x)*(b.y-o.y) - (b.x-o.x)*(a.y-o.y);
}

int lineCross(Point a, Point b, Point c, Point d, Point &p) {
	double s1, s2;
	s1=cross(a,b,c);
	s2=cross(a,b,d);
	if(sig(s1)==0 && sig(s2)==0)	return 2;
	if(sig(s2-s1)==0)	return 0;
	p.x = (c.x*s2-d.x*s1)/(s2-s1);
	p.y = (c.y*s2-d.y*s1)/(s2-s1); 
	return 1;
}

int find(double ang, Point &p) {
	double t1 = ang - ps[0].ang;
	if (t1 < 0) t1 += PI * 2;
	int lo = 0, hi = n - 1, ret = -1;
	while (lo <= hi) {
		int mid = (lo + hi) >> 1;
		double t2 = ps[mid].ang - ps[0].ang;
		if (sig(t2) < 0) t2 += PI * 2;
		if (sig(t2 - t1) <= 0) {
			ret = mid;
			lo = mid + 1;
		}
		else hi = mid - 1;
	}
	lineCross(ps[ret], ps[ret + 1], Point(0.0, 0.0), Point(cos(ang), sin(ang)), p);
	return ret;
}

double cover(double ang1, double ang2) {
	Point x, y;
	int idx1 = find(ang1, x), idx2 = find(ang2, y);
	if (idx1 == idx2) {
		if (sig(ang2 - ang1 - PI) >= 0) return sum[n] - (x - y).len();
		return (x - y).len();
	} else {
		idx1 = (idx1 + 1) % n;
		double ans = (ps[idx1] - x).len() + (ps[idx2] - y).len();
		if (idx1 <= idx2) ans += sum[idx2] - sum[idx1];
		else ans += sum[n] - (sum[idx1] - sum[idx2]);
		return ans;
	}
}

int main(int argc, char const *argv[])
{
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		ps[i].input();
		ps[i].getAngle();
	}
	ps[n] = ps[0];
	sum[0] = 0;
	for (int i = 1; i <= n; i++)
		sum[i] = sum[i - 1] + (ps[i] - ps[i - 1]).len();
	for (int i = 0; i < m; i++) {
		Point a, b;
		a.input(); b.input();
		a.getAngle(); b.getAngle();
		double x = min(a.ang, b.ang), y = max(a.ang, b.ang);
		if (sig(y - x - PI) >= 0) {
			vec.PB(MP(-PI, x));
			vec.PB(MP(y, PI));
		} else {
			vec.PB(MP(x, y));
		}
	}
	sort(vec.begin(), vec.end());
	double l = -PI, r = -PI;
	double ret = 0;
	for (vector<pair<double, double> >::iterator it = vec.begin(); it != vec.end(); it++) {
		if (sig(it->first - r) > 0) {
			ret += cover(l, r);
			l = it->first;
			r = it->second;
		} else {
			r = max(r, it->second);
		}
	}
	ret += cover(l, r);
	printf("%.12f\n", ret);
	return 0;
}