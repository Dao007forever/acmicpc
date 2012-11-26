/*
 * Author: Yang Zhang
 * Created Time: Sun 26 Aug 2012 08:13:35 PM CST
 * File Name: 3251.cpp
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
#define maxV 1010
#define maxE 400000
struct Dinic {
	int V, E;
	F cap[maxE], flow[maxE];
	int to[maxE], prev[maxE], idx[maxE];
	int level[maxV], used[maxV], last[maxV];
	bool mk[maxV];

	void init(int n) {
		V = n; E = 0;
		for (int i = 0; i < V; i++) last[i] = -1;
	}

	void addCap(int x, int y, int f, int id) {
		cap[E] = f; flow[E] = 0; to[E] = y; idx[E] = id; prev[E] = last[x]; last[x] = E; E++;
		cap[E] = 0; flow[E] = 0; to[E] = x; idx[E] = id; prev[E] = last[y]; last[y] = E; E++;
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

	//find S/T cuts
	void tra(int now) {
		mk[now] = true;
		for (int i = last[now], v; i != -1; i = prev[i])
			if (cap[i] - flow[i] > 0 && !mk[v = to[i]])
				tra(v);
	}
	//output the cut edges
	void output(int m) {
		vector<int> ans;
		for (int i = 0; i < E; i++) {
			if (idx[i << 1] > m) break;
			if (mk[to[(i << 1) | 1]] && !mk[to[i << 1]])
				ans.PB(idx[i << 1]);
		}
		sort(ans.begin(), ans.end());
		printf("%d", ans.size());
		for (int i = 0; i < ans.size(); i++)
			printf(" %d", ans[i]);
		printf("\n");
	}
}mf;

int main() {
	int Test;
	scanf("%d", &Test);
	for (int cas = 1; Test--; cas++) {
		int n, m, f;
		scanf("%d%d%d", &n, &m, &f);
		mf.init(n + 2);
		int source = 0, sink = n + 1;
		mf.addCap(source, 1, inf, 0);
		for (int i = 1; i <= m; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			mf.addCap(a, b, c, i);
		}
		int sum = 0;
		for (int i = 1; i <= f; i++) {
			int u, w;
			scanf("%d%d", &u, &w);
			sum += w;
			mf.addCap(u, sink, w, m + i);
		}
		int min_cut = mf.solve(source, sink);
		printf("Case %d: %d\n", cas, sum - min_cut);
		memset(mf.mk, 0, sizeof(mf.mk));
		mf.tra(source);
		mf.output(m);
	}
	return 0;
}

