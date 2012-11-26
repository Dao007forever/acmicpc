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

#define MAXN 205
int n;
struct City {
	int x, y;
}c[105];
struct Graph {
	int n, depth, size;
	int dfn[MAXN], low[MAXN], id[MAXN];
	bool vis[MAXN];
	vector<int> adj[MAXN];
	stack<int> S;

	void init(int n) {
		this->n = n;
		for (int i = 0; i <= 2 * n; i++)
			adj[i].clear();
		memset(dfn, -1, sizeof(dfn));
		memset(low, 0, sizeof(low));
		memset(vis, false, sizeof(vis));
		memset(id, 0, sizeof(id));
		while (!S.empty()) S.pop();
	}

	void addEdge(int a, int b) {
		//cout << a << " " << b << endl;
		adj[a].PB(b);
	}

	void Tarjan(int u) {
		dfn[u] = low[u] = depth++;
		S.push(u);
		vis[u] = true;
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i];
			if (dfn[v] == -1) {
				Tarjan(v);
				low[u] = min(low[u], low[v]);
			} else if (vis[v]) {
				low[u] = min(low[u], dfn[v]);
			}
		}
		if (low[u] == dfn[u]) {
			size++;
			int v;
			do {
				v = S.top();
				S.pop();
				id[v] = size;
				vis[v] = false;
			} while (u != v);
		}
	}

	bool twosat() {
		depth = 1; size = 0;
		for (int i = 0; i < 2 * n; i++)
			if (dfn[i] == -1) Tarjan(i);
		for (int i = 0; i < n; i++)
			if (id[i] == id[i + n]) return false;
		return true;
	}

}g;

bool check(int size) {
	g.init(n);
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (abs(c[i].x - c[j].x) >= size || abs(c[i].y - c[j].y) >= 2*size) {
				continue;
			}
			if (c[i].y == c[j].y) {
				g.addEdge(i, j + n); g.addEdge(j + n, i);
				g.addEdge(i + n, j); g.addEdge(j, i + n);
			} else if (abs(c[i].y - c[j].y) < size) {
				if (c[i].y > c[j].y) {
					g.addEdge(i + n, i); //i up
					g.addEdge(j, j + n); //j down
				} else {
					g.addEdge(j + n, j); //j up
					g.addEdge(i, i + n); //i down
				}
			} else if (abs(c[i].y - c[j].y) < 2*size) {
				if (c[i].y > c[j].y) {
					g.addEdge(i + n, j + n);//i down, j down
					g.addEdge(j, i);//j up, i up
				} else {
					g.addEdge(j + n, i + n); //j down, i down
					g.addEdge(i, j);//i up, j up
				}
			}
		}
	}
	bool flag = g.twosat();
	return flag;
}

int main(int argc, char const *argv[])
{
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d%d", &c[i].x, &c[i].y);
		}
		int lo = 0, hi = 0x3f3f3f3f, ret = -1;
		while (lo <= hi) {
			int mid = (lo + hi) >> 1;
			if (check(mid)) {
				ret = mid;
				lo = mid + 1;
			} else hi = mid - 1;
		}
		printf("%d\n", ret);
	}
	return 0;
}