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
	return (d>eps) - (d<-eps);
}
int n, m;
int adj[222][222], mate[222];
bool mk[222];

int dfs(int u) {
	for (int v = 0; v < m; v++) {
		if (adj[u][v] && !mk[v]) {
			mk[v] = true;
			if (mate[v] == -1 || dfs(mate[v])) {
				mate[v] = u;
				return 1;
			}
		}
	}
	return 0;
}

int maxMatch() {
	memset(mate, -1, sizeof(mate));
	int ret = 0;
	for (int i = 0; i < n; i++) {
		memset(mk, 0, sizeof(mk));
		ret += dfs(i);
	}
	return ret;
}

struct Point {
	double x, y;
	void input() {
		scanf("%lf%lf", &x, &y);
	}
}hawk[111], hole[111];

double dis(const Point &a, const Point &b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main(int argc, char const *argv[])
{
	double s, v;
	while (~scanf("%d%d%lf%lf", &n, &m, &s, &v)) {
		for (int i = 0; i < n; i++)
			hawk[i].input();
		for (int i = 0; i < m; i++)
			hole[i].input();
		memset(adj, 0, sizeof(adj));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				double t = dis(hawk[i], hole[j]) / v;
				if (sig(t - s) <= 0) {
					adj[i][j] = true;
				}
			}
		}
		int ret = maxMatch();
		printf("%d\n", n - ret);
	}
	return 0;
}