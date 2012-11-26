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
}a[105], b[105];
int n;
#define MAXN 205
struct Graph {
	int n, depth, size;
	int dfn[MAXN], low[MAXN], id[MAXN];
	bool vis[MAXN];
	vector<int> adj[MAXN];
	stack<int> S;

	void init(int n) {
		this->n = n;
		for (int i = 0; i <= 2 * n; i++)
			adj[i].clear();
		memset(dfn, -1, sizeof(dfn));
		memset(low, 0, sizeof(low));
		memset(vis, false, sizeof(vis));
		memset(id, 0, sizeof(id));
		while (!S.empty()) S.pop();
	}

	void addEdge(int a, int b) {
		adj[a].PB(b);
	}

	void Tarjan(int u) {
		dfn[u] = low[u] = depth++;
		S.push(u);
		vis[u] = true;
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i];
			if (dfn[v] == -1) {
				Tarjan(v);
				low[u] = min(low[u], low[v]);
			} else if (vis[v]) {
				low[u] = min(low[u], dfn[v]);
			}
		}
		if (low[u] == dfn[u]) {
			size++;
			int v;
			do {
				v = S.top();
				S.pop();
				id[v] = size;
				vis[v] = false;
			} while (u != v);
		}
	}

	bool twosat() {
		depth = 1; size = 0;
		for (int i = 0; i < 2 * n; i++)
			if (dfn[i] == -1) Tarjan(i);
		for (int i = 0; i < n; i++)
			if (id[i] == id[i + n]) return false;
		return true;
	}

}g;

bool touch(const Point &A, const Point &B, double dist) {
	double d = sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
	return sig(d - 2*dist) < 0;
}

bool check(double dist) {
	g.init(n);
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++) {
			if (touch(a[i], a[j], dist)) {
				g.addEdge(i, j + n);
				g.addEdge(j, i + n);
			}
			if (touch(a[i], b[j], dist)) {
				g.addEdge(i, j);
				g.addEdge(j + n, i + n);
			}
			if (touch(b[i], a[j], dist)) {
				g.addEdge(i + n, j + n);
				g.addEdge(j, i);
			}
			if (touch(b[i], b[j], dist)) {
				g.addEdge(i + n, j);
				g.addEdge(j + n, i);
			}
		}
	bool flag = g.twosat();
	return flag;
}

int main(int argc, char const *argv[])
{
	while (~scanf("%d", &n)) {
		for (int i = 0; i < n; i++) {
			a[i].input(); b[i].input();
		}
		double l = 0, r = 1e10, ret = 0.0;
		while (r - l > 1e-6) {
			double mid = (l + r) / 2;
			if (check(mid)) {
				ret = mid;
				l = mid;
			} else r = mid;
		}
		printf("%.2f\n", ret);
	}
	return 0;
}