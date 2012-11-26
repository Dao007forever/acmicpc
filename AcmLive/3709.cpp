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

typedef double F;
const double eps = 1e-6;
int sig(double d) {
	return (d > eps) - (d < -eps);
}
#define inf (1 << 29)
#define maxV 105
#define maxE 10005
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

	bool mkS[maxV];
	int tot;
	void tra(int u) {
		mkS[u] = true; tot++;
		for (int i = last[u], v; i != -1; i = prev[i]) {
			v = to[i];
			if (!mkS[v] && sig(cap[i] - flow[i]) > 0) {
				tra(v);
			}
		}
	}

	void output(int n) {
		printf("%d\n", tot - 1);
		for (int i = 1; i <= n; i++)
			if (mkS[i]) printf("%d\n", i);
	}
}mf;

int n, m;
int deg[maxV], edgeA[maxE], edgeB[maxE];
double search(double g) {
	mf.init(n + 2);
	int source = 0, sink = n + 1;
	for (int i = 1; i <= n; i++) {
		mf.addCap(source, i, m);
		mf.addCap(i, sink, m + 2 * g - deg[i]);
	}
	for (int i = 0; i < m; i++) {
		mf.addCap(edgeA[i], edgeB[i], 1);
		mf.addCap(edgeB[i], edgeA[i], 1);
	}
	double flow = mf.solve(source, sink);
	return ((double)n * m - flow) / 2.0;
}

int main(int argc, char const *argv[])
{
	int blank = false;
	while (~scanf("%d%d", &n, &m)) {
		if (blank) puts("");
		blank = true;
		memset(deg, 0, sizeof(deg));
		for (int i = 0; i < m; i++) {
			scanf("%d%d", &edgeA[i], &edgeB[i]);
			deg[edgeA[i]]++; deg[edgeB[i]]++;
		}
		if (m == 0) {
			printf("1\n1\n");
			continue;
		}
		double lo = 0, hi = m;
		while (hi - lo > 1.0/n/n) {
			double mid = (lo + hi) / 2.0;
			if (search(mid) > eps) {
				lo = mid;
			} else hi = mid;
		}
		search(lo);
		mf.tot = 0;
		memset(mf.mkS, 0, sizeof(mf.mkS));
		mf.tra(0);
		mf.output(n);
	}
	return 0;
}