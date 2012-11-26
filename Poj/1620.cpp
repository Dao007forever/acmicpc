/*
 * Author: Yang Zhang
 * Created Time: Tue 11 Sep 2012 04:17:48 PM CST
 * File Name: 1620.cpp
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

int n;
struct Point {
	double x, y;
	Point() {}
	Point(int _x, int _y) : x(_x), y(_y) {}
	void input() {
		scanf("%lf%lf", &x, &y);
	}
	double dist(const Point &p) {
		return (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y);
	}
}ps[15];
int col[15];
int ret;
bool adj[15][15];

void dfs(int u, int sum) {
	if (u == n) {
		ret = min(ret, sum);
		return;
	}
	if (sum >= ret) return;
	vector<bool> used(n, false);
	for (int i = 0; i < n; i++)
		if (adj[u][i]) {
			used[col[i]] = true;
		}
	for (int i = 1; i <= sum; i++) {
		if (used[i]) continue;
		col[u] = i;
		dfs(u + 1, sum);
		col[u] = 0;
	}
	col[u] = sum + 1;
	dfs(u + 1, sum + 1);
	col[u] = 0;
}

int main() {
	int cas = 1;
	while (scanf("%d", &n) && n) {
		for (int i = 0; i < n; i++)
			ps[i].input();
		memset(adj, 0, sizeof(adj));
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++)
				if (ps[i].dist(ps[j]) <= 400.0)
					adj[i][j] = adj[j][i] = true;
		ret = 10000;
		memset(col, 0, sizeof(col));
		dfs(0, 0);
		printf("The towers in case %d can be covered in %d frequencies.\n", cas++, ret);
	}
	return 0;
}

