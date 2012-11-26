/*
 * Author: Yang Zhang
 * Created Time: Sun 16 Sep 2012 12:48:13 PM CST
 * File Name: main.cpp
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
#define maxV 810
#define maxE 400000
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
//		cout << x << " " << y << " " << f << endl;
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
	void output(int s) {
		int ret = 0;
		for (int i = last[s]; i != -1; i = prev[i])
			ret += (cap[i] - flow[i] == 0);
		printf("%d\n", ret);
	}
}mf;

int main() {
	int N, F, D;
	while (~scanf("%d%d%d", &N, &F, &D)) {
		mf.init(2*N + F + D + 2);
		int source = 0, sink = 2*N + F + D + 1;
		for (int i = 1; i <= N; i++) {
			mf.addCap(i, N + i, 1);
		}
		for (int i = 1; i <= F; i++) {
			int x;
			scanf("%d", &x);
			mf.addCap(source, 2*N + i, x);
		}
		for (int i = 1; i <= D; i++) {
			int x;
			scanf("%d", &x);
			mf.addCap(2*N + F + i, sink, x);
		}
		char st[222];
		for (int i = 1; i <= N; i++) {
			scanf("%s", st + 1);
			for (int j = 1; j <= F; j++) {
				if (st[j] == 'Y') {
					mf.addCap(2*N+j, i, 1);
				}
			}
		}
		for (int i = 1; i <= N; i++) {
			scanf("%s", st + 1);
			for (int j = 1; j <= D; j++) {
				if (st[j] == 'Y') {
					mf.addCap(N+i, 2*N + F + j, 1);
				}
			}
		}
		int ret = mf.solve(source, sink);
		printf("%d\n", ret);
	}
	return 0;
}

