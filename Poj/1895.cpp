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
#define maxV 125010
#define maxE 6250000
int n, m, K, S, T;
int edgeA[405], edgeB[405];
struct Dinic {
	int V, E;
	F cap[maxE], flow[maxE];
	int to[maxE], prev[maxE];
	int level[maxV], used[maxV], last[maxV];

	void init(int n) {
		V = n; E = 0;
		for (int i = 0; i < V; i++) last[i] = -1;
	}

	void addCap(int x, int y, F f) {
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

	int g[111][111];
	vector<pair<int, int> > ans[111];
	vector<int> path[111][111];
	void output(int level) {
		for (int i = 0; i <= level; i++)
			for (int j = 1; j <= n; j++)
				path[i][j].clear();
		for (int i = 0; i <= level; i++)
			ans[i].clear();
		for (int i = 1; i <= K; i++)
			path[0][S].PB(i);
		for (int i = 0; i < level; i++) {
			memset(g, 0, sizeof(g));
			for (int u = 1; u <= n; u++) {
				int idx = i * n + u;
				for (int k = last[idx]; k != -1; k = prev[k]) {
					int v = to[k], f = flow[k], c = cap[k];
					if (c == 0 || f == 0) continue;
					if (v != (i + 1) * n + u && v != V - 1) g[u][v - (i + 1) * n] = true;
				}
			}
			for (int j = 0; j < m; j++) {
				int a = edgeA[j], b = edgeB[j];
				if (g[a][b] && g[b][a]) {
					g[a][b] = g[b][a] = false;
				}
			}
			for (int j = 1; j <= n; j++) {
				if (path[i][j].size() == 0) continue;
				for (int k = 1; k <= n; k++) {
					if (g[j][k]) {
						int idx = *(path[i][j].rbegin()); path[i][j].pop_back();
						path[i + 1][k].PB(idx);
						ans[i].PB(MP(idx, k));
					}
				}
				for (vector<int>::iterator it = path[i][j].begin(); it != path[i][j].end(); it++)
					path[i + 1][j].PB(*it);
			}
		}
		for (int i = 0; i < level; i++) {
			printf("%d ", ans[i].size());
			for (int j = 0; j < ans[i].size(); j++)
				printf("%d %d ", ans[i][j].first, ans[i][j].second);
			printf("\n");
		}
	}
}mf;

bool check(int level) {
	mf.init((level + 1) * n + 2);
	int source = 0, sink = (level + 1) * n + 1;
	mf.addCap(source, S, K);
	for (int i = 0; i < level; i++) {
		for (int j = 1; j <= n; j++) {
			int a = i * n + j, b = (i + 1) * n + j;
			mf.addCap(a, b, inf);
		}
		for (int j = 0; j < m; j++) {
			int a = i * n + edgeA[j], b = (i + 1) * n + edgeB[j];
			mf.addCap(a, b, 1);
			a = i * n + edgeB[j], b = (i + 1) * n + edgeA[j];
			mf.addCap(a, b, 1);
		}
	}
	mf.addCap(level * n + T, sink, K);
	int ret = mf.solve(source, sink);
	return ret >= K;
}

int main(int argc, char const *argv[])
{
	while (~scanf("%d%d%d%d%d", &n, &m, &K, &S, &T)) {
		for (int i = 0; i < m; i++) {
			scanf("%d%d", &edgeA[i], &edgeB[i]);
		}
		int lo = 0, hi = n + K, ret = -1;
		while (lo <= hi) {
			int mid = (lo + hi) >> 1;
			if (check(mid)) {
				ret = mid;
				hi = mid - 1;
			} else lo = mid + 1;
		}
		check(ret);
		printf("%d\n", ret);
		mf.output(ret);
	}
	return 0;
}
