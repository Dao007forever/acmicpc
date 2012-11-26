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
#define maxV 105
#define maxE 40005
int n, m;
int ind[maxV], outd[maxV], diff[maxV];
int g[maxV][maxV];
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

	void tra(int u) {
		for (int v = 0; v < n; v++)
			if (g[u][v]) {
				printf(" %d", v + 1);
				outd[u]--; ind[v]--;
				g[u][v]--;
				tra(v);
				break;
			}
	}

	void output() {
		for (int u = 0; u < n; u++) {
			for (int i = last[u]; i != -1; i = prev[i]) {
				int v = to[i], f = flow[i];
				if (v < n && f > 0) {
					g[u][v] += f;
					outd[u] += f;
					ind[v] += f;
				}
			}
		}

		for (int st = 0; st < n; st++) {
			while (outd[st] > ind[st]) {
				printf("%d", st + 1);
				tra(st);
				printf("\n");
			}
		}
	}
}mf;

int main(int argc, char const *argv[])
{
	while (~scanf("%d", &n) && n) {
		m = 0;
		memset(ind, 0, sizeof(ind));
		memset(outd, 0, sizeof(outd));
		memset(diff, 0, sizeof(diff));
		memset(g, 0, sizeof(g));
		mf.init(n + 2);
		int source = n, sink = n + 1;
		for (int i = 0; i < n; i++) {
			int k, x;
			scanf("%d", &k);
			outd[i] = k;
			while (k--) {
				scanf("%d", &x); x--;
				ind[x]++;
				g[i][x]++;
				mf.addCap(i, x, inf);
			}
		}
		int sum = 0;
		for (int i = 0; i < n; i++) {
			diff[i] = ind[i] - outd[i];
			if (diff[i] > 0) {
				mf.addCap(source, i, diff[i]);
				sum += diff[i];
			} else {
				mf.addCap(i, sink, -diff[i]);
			}
		}
		int ret = mf.solve(source, sink);
		printf("%d\n", sum - ret);
		mf.output();
	}
	return 0;
}