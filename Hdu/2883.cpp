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
#define maxV 1010
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
		//cout << x << " " << y << " " << f << endl;
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

struct Custom {
	int n, t, s, e;
	void input() {
		scanf("%d%d%d%d", &s, &n, &e, &t);
	}
}c[205];
int main(int argc, char const *argv[])
{
	int n, m;
	while (~scanf("%d%d", &n, &m)) {
		vector<int> vec;
		map<int, int> mp;
		for (int i = 0; i < n; i++) {
			c[i].input();
			vec.PB(c[i].s); vec.PB(c[i].e);
		}
		sort(vec.begin(), vec.end());
		vec.resize(unique(vec.begin(), vec.end()) - vec.begin());
		for (int i = 0; i < vec.size(); i++)
			mp[vec[i]] = i;
		int k = vec.size();
		mf.init(n + k - 1 + 2);
		int source = n + k - 1, sink = n + k - 1 + 1;
		for (int i = 0; i < vec.size() - 1; i++)
			mf.addCap(n + i, sink, m * (vec[i + 1] - vec[i]));
		int sum = 0;
		for (int i = 0; i < n; i++) {
			sum += c[i].n * c[i].t;
			mf.addCap(source, i, c[i].n * c[i].t);
			int l = mp[c[i].s], r = mp[c[i].e];
			for (int j = l; j < r; j++)
				mf.addCap(i, n + j, inf);
		}
		int ret = mf.solve(source, sink);
		printf("%s\n", ret == sum ? "Yes" : "No");
	}
	return 0;
}