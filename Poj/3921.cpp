/*
 * Author: Yang Zhang
 * Created Time: Wed 12 Sep 2012 07:10:06 PM CST
 * File Name: 3921.cpp
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

typedef int F;
#define inf (1 << 29)
#define maxV 110
#define maxE 40000
struct Dinic {
	int V, E;
	F cap[maxE], flow[maxE];
	int to[maxE], prev[maxE];
	int level[maxV], used[maxV], last[maxV];

	void init(int n) {
		V = n; E = 0;
		for (int i = 0; i < V; i++) last[i] = -1;
	}

	void addCap(int x, int y, int f) {
		cap[E] = f; flow[E] = 0; to[E] = y; prev[E] = last[x]; last[x] = E; E++;
		cap[E] = 0; flow[E] = 0; to[E] = x; prev[E] = last[y]; last[y] = E; E++;
	}

	bool bfs(int s, int t) {
		for (int i = 0; i < V; i++)
			level[i] = -1;
		queue<int> q;
		q.push(s); level[s] = 0;
		while (!q.empty()) {
			int x = q.front(); q.pop();
			for (int i = last[x]; i != -1; i = prev[i])
				if (level[to[i]] == -1 && cap[i] > flow[i]) {
					q.push(to[i]);
					level[to[i]] = level[x] + 1;
				}
		}
		return (level[t] != -1);
	}

	F dfs(int v, int t, F f) {
		if (v == t) return f;
		for (int i = used[v]; i != -1; used[v] = i = prev[i])
			if (level[to[i]] > level[v] && cap[i] > flow[i]) {
				F tmp = dfs(to[i], t, min(f, cap[i] - flow[i]));
				if (tmp > 0) {
					flow[i] += tmp;
					flow[i ^ 1] -= tmp;
					return tmp;
				}
			}
		return 0;
	}

	F solve(int s, int t) {
		while (bfs(s, t)) {
			for (int i = 0; i < V; i++) used[i] = last[i];
			while (dfs(s, t, inf) != 0);
		}
		F ans = 0;
		for (int i = last[s]; i != -1; i = prev[i])
			ans += flow[i];
		return ans;
	}
}mf;

int n, m, limit;
vector<pair<int, int> > edge;
int d[55][55];

int main() {
	while (~scanf("%d%d%d", &n, &m, &limit)) {
		if (n == 0 && m == 0 && limit == 0) break;
		edge.clear();
		memset(d, 63, sizeof(d));
		mf.init(2 * n);
		for (int i = 0; i < m; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			a--; b--;
			d[a][b] = 1;
			mf.addCap(a + n, b, 1);
		}
		for (int k = 0; k < n; k++)
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
		mf.addCap(0, 0 + n, inf);
		mf.addCap(n - 1, n - 1 + n, inf);
		for (int i = 1; i < n - 1; i++)
			if (d[0][i] + d[i][n - 1] <= limit) {
				mf.addCap(i, i + n, 1);
				printf("Vertex %d\n", i);
			}

		int ret = mf.solve(0, 2 * n - 1);
		printf("%d\n", ret);
	}
	return 0;
}

