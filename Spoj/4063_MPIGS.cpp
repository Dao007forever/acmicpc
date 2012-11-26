/*
 * Author: Yang Zhang
 * Created Time: Tue 04 Sep 2012 09:43:02 PM CST
 * File Name: 4063_MPIGS.cpp
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
#define inf (1 << 20)
#define maxV 2000
#define maxE 1000*maxV
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

int n, m;
int p[maxV];

int main() {
	scanf("%d%d", &m, &n);
	memset(p, 0, sizeof(p));
	mf.init(n + m + 3);
	int source = n + m + 1, sink = n + m + 2;
	for (int i = 1; i <= m; i++) {
		int x;
		scanf("%d", &x);
		mf.addCap(n + i, sink, x);
	}
	for (int i = 1; i <= n; i++) {
		int k, x, b;
		scanf("%d", &k);
		for (; k--; ) {
			scanf("%d", &x);
			if (p[x]) {
				mf.addCap(i, p[x], inf);
			} else {
				mf.addCap(i, n + x, inf);
				p[x] = i;
			}
		}
		scanf("%d", &b);
		mf.addCap(source, i, b);
	}
	int ret = mf.solve(source, sink);
	printf("%d\n", ret);
	return 0;
}
