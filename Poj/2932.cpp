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

#define MAXN 40005
const double eps = 1e-8;
int sig(double d) {
	return (d > eps) - (d < -eps);
}
double orix, oriy;
struct Point {
	double x, y;
	Point() {}
	Point(double x, double y) : x(x), y(y) {}
	double dist(const Point &pt) {
		return sqrt((x - pt.x) * (x - pt.x) + (y - pt.y) * (y - pt.y));
	}
};
struct Circle {
	Point o;
	double radis;
	bool inside(Circle &pt) {
		double d = o.dist(pt.o);
		return sig(radis - (d + pt.radis)) >= 0;
	}
	void input() {
		scanf("%lf%lf%lf", &radis, &o.x, &o.y);
	}
}c[MAXN];
struct event {
	double x;
	int idx, type;
	event() {}
	event(double x, int idx, int type) : x(x), idx(idx), type(type) {}
	bool operator < (const event &pt) const {
		return sig(x - pt.x) < 0;
	}
};
struct node {
	double y;
	int idx;
	node() {}
	node(double y, int idx) : y(y), idx(idx) {}
	bool operator == (const node &pt) const {
		return sig(y - pt.y) == 0 && idx == pt.idx;
	}
	bool operator < (const node &pt) const {
		return sig(y - pt.y) < 0;
	}
};
int n;
vector<event> vec;
set<node> st;
bool vis[MAXN];

void output() {
	for (set<node>::iterator it = st.begin(); it != st.end(); it++)
		cout << it->y << " " << it->idx << endl;
}

int main(int argc, char const *argv[])
{
	while (~scanf("%d", &n)) {
		vec.clear();
		memset(vis, 0, sizeof(vis));
		for (int i = 0; i < n; i++) {
			c[i].input();
			vec.PB(event(c[i].o.x - c[i].radis, i, 0));
			vec.PB(event(c[i].o.x + c[i].radis, i, 1));
		}
		sort(vec.begin(), vec.end());
		st.clear();
		for (int i = 0; i < vec.size(); i++) {
			int idx = vec[i].idx;
			if (vec[i].type == 0) {
				node now = node(c[idx].o.y, idx);
				st.insert(now);
				set<node>::iterator it = st.find(now);
				//output();
				set<node>::iterator p1 = it, p2 = ++it;
				if (p1 != st.begin()) {
					p1--;
					if (c[p1->idx].inside(c[idx])) {
						vis[idx] = true;
					}
				}
				if (p2 != st.end()) {
					if (c[p2->idx].inside(c[idx])) {
						vis[idx] = true;
					}
				}
				if (vis[idx]) {
					st.erase(now);
				}
			} else {
				node now = node(c[idx].o.y, idx);
				if (!vis[idx]) {
					st.erase(now);
				}
			}
		}
		int ret = 0;
		for (int i = 0; i < n; i++)
			ret += vis[i] == 0;
		printf("%d\n", ret);
		bool blank = false;
		for (int i = 0; i < n; i++) {
			if (!vis[i]) {
				if (blank) printf(" ");
				blank = true;
				printf("%d", i + 1);
			}
		}
		puts("");
	}
	return 0;
}