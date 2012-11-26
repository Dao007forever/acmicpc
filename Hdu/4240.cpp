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

typedef int F;
#define inf (1 << 29)
#define maxV 610
#define maxE 400000
struct Dinic {
	int V, E;
	F cap[maxE], flow[maxE];
	int to[maxE], prev[maxE];
	int level[maxV], used[maxV], last[maxV];
	F g[maxV];

	void init(int n) {
		V = n; E = 0;
		for (int i = 0; i < V; i++) last[i] = -1;
	}

	void addCap(int x, int y, F f) {
		cap[E] = f; flow[E] = 0; to[E] = y; prev[E] = last[x]; last[x] = E; E++;
		cap[E] = 0; flow[E] = 0; to[E] = x; prev[E] = last[y]; last[y] = E; E++;
	}

	pair<F, F> bfs(int s, int t) {
		for (int i = 0; i < V; i++)
			g[i] = inf;
		for (int i = 0; i < V; i++)
			level[i] = -1;
		queue<int> q;
		q.push(s); level[s] = 0;
		while (!q.empty()) {
			int x = q.front(); q.pop();
			for (int i = last[x]; i != -1; i = prev[i])
				if (level[to[i]] == -1 && cap[i] > flow[i]) {
					if (g[to[i]] == inf) {
						g[to[i]] = min(g[x], cap[i]);
					} else {
						if (cap[i] < g[to[i]]) {
							g[to[i]] = max(g[x], cap[i]);
						} else {
							g[to[i]] = g[x];
						}
					}
					q.push(to[i]);
					level[to[i]] = level[x] + 1;
				}
		}
		return MP(level[t] != -1, g[t]);
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

	pair<F, F> solve(int s, int t) {
		bool first = true;
		int minc = 0;
		while (true) {
			pair<F, F> tmp = bfs(s, t);
			if (!tmp.first) break;
			if (first) {
				first = false;
				minc = tmp.second;
			}
			for (int i = 0; i < V; i++) used[i] = last[i];
			while (dfs(s, t, inf) != 0);
		}
		F ans = 0;
		for (int i = last[s]; i != -1; i = prev[i])
			ans += flow[i];
		return MP(ans, minc);
	}
}mf;

int main(int argc, char const *argv[])
{
	int Test;
	int cas, n, m, source, sink;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d%d%d%d%d", &cas, &n, &m, &source, &sink);
		mf.init(n);
		for (int i = 0; i < m; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			mf.addCap(a, b, c);
		}
		pair<int, int> ret = mf.solve(source, sink);
		printf("%d %.3f\n", cas, (double)ret.first / ret.second);
	}
	return 0;
}