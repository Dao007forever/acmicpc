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

int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};
int r, c, v0, v1;
int p[25][25];

int getID(int i, int j) {
	return (i - 1) * c + j;
}

int main(int argc, char const *argv[])
{
	int Test;
	scanf("%d", &Test);
	for (int cas = 1; Test--; cas++) {
		printf("Case %d:\n", cas);
		scanf("%d%d%d%d", &r, &c, &v0, &v1);
		for (int i = 1; i <= r; i++) {
			for (int j = 1; j <= c; j++) {
				scanf("%d", &p[i][j]);
			}
		}
		mf.init(2*r*c + 2);
		int source = 0, sink = 2*r*c + 1;
		for (int i = 1; i <= r; i++)
			for (int j = 1; j <= c; j++) {
				int idx = getID(i, j);
				mf.addCap(source, idx, abs(p[i][j] - v0));
				mf.addCap(idx, sink, abs(p[i][j] - v1));
				for (int k = 0; k < 4; k++) {
					int x = i + dx[k], y = j + dy[k];
					if (x >= 1 && x <= r && y >= 1 && y <= c) {
						mf.addCap(idx, getID(x, y), abs(p[i][j] - p[x][y]));
					}
				}
			}
		int ret = mf.solve(source, sink);
		printf("%d\n", ret);
		if (Test) puts("");
	}
	return 0;
}