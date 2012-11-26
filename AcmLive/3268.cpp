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
#define maxV 1505
#define maxE 600000
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
}mf;

int n, m;
vector<int> choose[maxV];
bool check(int lim) {
	mf.init(n + m + 2);
	int source = n + m, sink = n + m + 1;
	for (int i = 0; i < n; i++) {
		mf.addCap(source, i, 1);
		for (int j = 0; j < choose[i].size(); j++) {
			mf.addCap(i, n + choose[i][j], 1);
		}
	}
	for (int i = 0; i < m; i++)
		mf.addCap(n + i, sink, lim);
	return mf.solve(source, sink) >= n;
}
int main(int argc, char const *argv[])
{

	while (~scanf("%d%d\n", &n, &m) && n + m) {
		for (int i = 0; i < n; i++) {
			choose[i].clear();
			string input, name;
			istringstream iss;
			getline(cin, input);
			iss.str(input);
			iss >> name;
			int x;
			while (iss >> x) {
				choose[i].PB(x);
			}
		}

		int lo = 0, hi = n, ret = -1;
		while (lo <= hi) {
			int mid = (lo + hi) >> 1;
			if (check(mid)) {
				ret = mid;
				hi = mid - 1;
			} else lo = mid + 1;
		}
		printf("%d\n", ret);
	}
	return 0;
}