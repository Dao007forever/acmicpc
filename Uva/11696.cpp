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
const double eps = 1e-8;
const double PI = acos(-1.0);
int sig(double d) {
	return (d > eps) - (d < -eps);
}
struct Point {
	int x, y;
	Point() {}
	Point(int x, int y) : x(x), y(y) {}
	void input() {
		scanf("%d%d", &x, &y);
	}
	int dist(const Point &pt) {
		return (x - pt.x) * (x - pt.x) + (y - pt.y) * (y - pt.y);
	}
}ps[MAXN];
struct Circle {
	Point o;
	int radis;
	void input() {
		scanf("%d%d%d", &o.x, &o.y, &radis);
	}
}cir[MAXN];
struct event {
	double ang;
	int type, id, dis;
	bool operator < (const event &pt) const {
		if (sig(ang - pt.ang) != 0) return ang < pt.ang;
		return type > pt.type;
	}
};
int n, m;
int p[MAXN];

int find(int x) {
	if (p[x] == x) return x;
	return p[x] = find(p[x]);
}

void Union(int x, int y) {
	//cout << x << " " << y << endl;
	x = find(x), y = find(y);
	p[x] = y;
}

void solve() {
	for (int i = 0; i < n; i++) {
		vector<event> vec;
		for (int j = i + 1; j < n; j++) {
			event tmp;
			tmp.ang = atan2((double)ps[j].y - ps[i].y, (double)ps[j].x - ps[i].x);
			if (sig(tmp.ang) < 0) tmp.ang += 2.0 * PI;
			tmp.dis = ps[i].dist(ps[j]);
			tmp.type = 0;
			tmp.id = j;
			vec.PB(tmp);
		}
		for (int j = 0; j < m; j++) {
			double alpha = atan2(cir[j].o.y - ps[i].y, cir[j].o.x - ps[i].x);
			int d = ps[i].dist(cir[j].o);
			double delta = asin((double)cir[j].radis / sqrt(d));
			double a1 = alpha - delta, a2 = alpha + delta;
			event tmp;
			if (sig(a1) < 0) {
				a1 += 2.0 * PI; a2 += 2.0 * PI;
			}
			d -= cir[j].radis * cir[j].radis;
			tmp.dis = d;
			if (sig(a2 - 2.0 * PI) <= 0) {
				tmp.ang = a1;
				tmp.type = 1;
				vec.PB(tmp);
				tmp.ang = a2;
				tmp.type = -1;
				vec.PB(tmp);
			} else {
				tmp.ang = a1;
				tmp.type = 1;
				vec.PB(tmp);
				tmp.ang = 2.0 * PI;
				tmp.type = -1;
				vec.PB(tmp);

				tmp.ang = 0.0;
				tmp.type = 1;
				vec.PB(tmp);
				tmp.ang = a2 - 2.0 * PI;
				tmp.type = -1;
				vec.PB(tmp);
			}
		}
		sort(vec.begin(), vec.end());
		multiset<int> st;
		for (vector<event>::iterator it = vec.begin(); it != vec.end(); it++) {
			if (it->type == 0) {
				if (st.empty()) {
					Union(i, it->id);
				} else if (it->dis - *st.begin() < 0) {
					Union(i, it->id);
				}
			} else if (it->type == 1) {
				st.insert(it->dis);
			} else {
				multiset<int>::iterator k = st.find(it->dis);
				st.erase(k);
			}
		}
	}
}

int main(int argc, char const *argv[])
{
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; i++)
			p[i] = i;
		for (int i = 0; i < n; i++)
			ps[i].input();
		for (int i = 0; i < m; i++)
			cir[i].input();
		if (m == 0) {
			puts("0");
			continue;
		}
		solve();
		int ret = 0;
		for (int i = 0; i < n; i++)
			ret += p[i] == i;
		printf("%d\n", --ret);
	}
	return 0;
}