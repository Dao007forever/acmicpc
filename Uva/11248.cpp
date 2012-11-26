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
#define maxV 205
#define maxE 20005
int n, m, C;
int edgeA[maxE], edgeB[maxE], idx[maxE];
struct Dinic {
	int V, E;
	F cap[maxE], flow[maxE];
	int to[maxE], prev[maxE];
	int level[maxV], used[maxV], last[maxV];

	void init(int n) {
		V = n; E = 0;
		for (int i = 0; i < V; i++) last[i] = -1;
	}

	int addCap(int x, int y, F f) {
		int ret = E;
		cap[E] = f; flow[E] = 0; to[E] = y; prev[E] = last[x]; last[x] = E; E++;
		cap[E] = 0; flow[E] = 0; to[E] = x; prev[E] = last[y]; last[y] = E; E++;
		return ret;
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

	bool mkS[maxV], mkT[maxV];
	int rest;
	void traS(int u) {
		mkS[u] = true;
		for (int i = last[u], v; i != -1; i = prev[i]) {
			if (cap[i] - flow[i] > 0 && !mkS[v = to[i]]) {
				traS(v);
			}
		}
	}

	void traT(int u) {
		mkT[u] = true;
		for (int i = last[u], v; i != -1; i = prev[i]) {
			if (cap[i ^ 1] - flow[i ^ 1] > 0 && !mkT[v = to[i]]) {
				traT(v);
			}
		}
	}

	int tmpflow[maxE];
	void work(int s, int t) {
		memset(mkS, 0, sizeof(mkS));
		memset(mkT, 0, sizeof(mkT));
		traS(s);
		traT(t);
		vector<pair<int, int> > ans;
		for (int i = 0; i < m; i++) {
			int a = edgeA[i], b = edgeB[i];
			if (mkS[a] && !mkS[b] && mkT[b] && !mkT[a]) {
				int id = idx[i];
				int temp = cap[id];
				cap[id] = C;

				memcpy(tmpflow, flow, sizeof(flow));
				int newFlow = solve(s, t);
				if (newFlow >= C) ans.PB(MP(a, b));
				memcpy(flow, tmpflow, sizeof(tmpflow));

				cap[id] = temp;
			}
		}
		if (ans.size() == 0) {
			puts("not possible");
		} else {
			printf("possible option:");
			sort(ans.begin(), ans.end());
			ans.resize(unique(ans.begin(), ans.end()) - ans.begin());
			for (int i = 0; i < ans.size(); i++) {
				printf("(%d,%d)", ans[i].first + 1, ans[i].second + 1);
				if (i != ans.size() - 1) printf(",");
				else printf("\n");
			}
		}
	}
}mf;

int main(int argc, char const *argv[])
{
	int cas = 1;
	while (~scanf("%d%d%d", &n, &m, &C)) {
		if (n == 0 && m == 0 && C == 0) break;
		printf("Case %d: ", cas++);
		if (n == 1) {
			puts("possible");
			continue;
		}
		mf.init(n);
		for (int i = 0; i < m; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			a--; b--;
			edgeA[i] = a; edgeB[i] = b;
			idx[i] = mf.addCap(a, b, c);
		}
		F flow = mf.solve(0, n - 1);
		if (flow >= C) {
			puts("possible");
		} else {
			mf.work(0, n - 1);
		}
	}
	return 0;
}
