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

#define MAXN 2700
const double inf = 1e20;
const double eps = 1e-8;
int sig(double d) {
	return (d > eps) - (d < -eps);
}
int mk[MAXN], cx[MAXN], cy[MAXN];
vector<int> adj[MAXN];

void addEdge(int u, int v) {
	adj[u].PB(v);
	//cout << u << "->" << v << endl;
}

struct Point {
	double x, y;
	Point() {}
	Point(double x, double y) : x(x), y(y) {}
	void input() {
		scanf("%lf%lf", &x, &y);
	}
}ps[55], pt[55];
int n, m;
double t1, t2, v;

int path(int u) {
	for (int i = 0, v; i < adj[u].size(); i++) {
		if (!mk[v = adj[u][i]]) {
			mk[v] = 1;
			if (cy[v] == -1 || path(cy[v])) {
				cx[u] = v;
				cy[v] = u;
				return 1;
			}
		}
	}
	return 0;
}

int MaxMatch() {
	memset(cx, -1, sizeof(cx));
	memset(cy, -1, sizeof(cy));
	int ret = 0;
	for (int i = 1; i <= m; i++) {
		if (cx[i] == -1) {
			memset(mk, 0, sizeof(mk));
			ret += path(i);
		}
	}
	return ret;
}

double dist(const Point &A, const Point &B) {
	return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

int getID(int x, int y) {
	return m + (y - 1) * n + x;
}

bool check(double lim) {
	for (int i = 0; i <= m; i++) adj[i].clear();
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			double d = dist(pt[i], ps[j]);
			for (int k = 1; k <= m; k++) {
				double t = d / v + t1 * k + t2 * (k - 1);
				if (sig(t - lim) <= 0) {
					int idx = getID(j, k);
					addEdge(i, idx);
				} else break;
			}
		}
	}
	int ret = MaxMatch();
	return ret == m;
}

int main(int argc, char const *argv[])
{
	while (~scanf("%d%d%lf%lf%lf", &n, &m, &t1, &t2, &v)) {
		t1 /= 60;
		for (int i = 1; i <= m; i++)
			pt[i].input();
		for (int i = 1; i <= n; i++)
			ps[i].input();
		//cout << check(92) << endl;
		//return 0;
		double lo = 0, hi = 1e10, ret = 0;
		while (hi - lo > eps) {
			double mid = (lo + hi) / 2;
			if (check(mid)) {
				ret = mid;
				hi = mid;
			} else lo = mid;
		}
		printf("%.6f\n", ret);
	}
	return 0;
}