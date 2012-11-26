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

#define MAXN 800000
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
		for (int i = 1; i <= 2 * n; i++)
			if (dfn[i] == -1) Tarjan(i);
		for (int i = 1; i <= n; i++)
			if (id[i] == id[i + n]) return false;
		return true;
	}

}g;

int dx[5] = {0, 1, 0, -1, 0};
int dy[5] = {0, 0, 1, 0, -1};
int n, m;

int id(int i, int j) {
	return (i - 1) * m + j;
}

bool work() {
	cin >> n >> m;
	map<pair<int, int>, int> mp;
	vector<string> s(n + 2);
	for (int i = 1; i <= n; i++)
		cin >> s[i], s[i] = '.' + s[i] + '.';
	s[0].append(m + 2, '.');
	s[n + 1].append(m + 2, '.');
	int cnt = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (s[i][j] == 'B')
				for (int k = 1; k <= 4; k++)
					if (s[i + dx[k]][j + dy[k]] == 'W')
						mp[MP(id(i, j), id(i + dx[k], j + dy[k]))] = ++cnt;
	int num_B = 0, num_W = 0;
	g.init(cnt);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (s[i][j] == 'B') {
				num_B++;
				for (int k = 1; k <= 2; k++) {
					int k1 = s[i + dx[k]][j + dy[k]] == 'W', k2 = s[i + dx[k + 2]][j + dy[k + 2]] == 'W';
					int O = id(i, j), A = id(i + dx[k], j + dy[k]), B = id(i + dx[k + 2], j + dy[k + 2]);
					if (!k1 && !k2) return false;
					if (k1 + k2 == 1) {
						if (k1) {
							g.addEdge(mp[MP(O, A)] + cnt, mp[MP(O, A)]);//must choose <O,A>
						} else {
							g.addEdge(mp[MP(O, B)] + cnt, mp[MP(O, B)]);//must choose <O,B>
						}
					} else if (k1 + k2 == 2) {
						//g.addEdge(mp[MP(O, A)], mp[MP(O, B)] + cnt);//choose <O,A>, not choose <O,B>
						//g.addEdge(mp[MP(O, B)], mp[MP(O, A)] + cnt);//choose <O,B>, not choose <O,A>
						g.addEdge(mp[MP(O, A)] + cnt, mp[MP(O, B)]);//not choose <O,A>, choose <O,B>
						g.addEdge(mp[MP(O, B)] + cnt, mp[MP(O, A)]);//not choose <O,B>, choose <O,A>
					}
				}
			} else if (s[i][j] == 'W') {
				num_W++;
				vector<int> f;
				for (int k = 1; k <= 4; k++)
					if (s[i + dx[k]][j + dy[k]] == 'B')
						f.PB(id(i + dx[k], j + dy[k]));
				if (f.size() == 0) return false;
				else {
					for (int x = 0; x < f.size(); x++)
						for (int y = x + 1; y < f.size(); y++) {
							int O1 = f[x], O2 = f[y], A = id(i, j);
							g.addEdge(mp[MP(O1, A)], mp[MP(O2, A)] + cnt);//choose <O1,A>, not choose <O2,A>
							g.addEdge(mp[MP(O2, A)], mp[MP(O1, A)] + cnt);//choose <O2,A>, not choose <O1,A>
						}
				}
			}
	return (num_W == 2 * num_B && g.twosat());
}

int main() {
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		if (work()) puts("YES");
		else puts("NO");
	}
	return 0;
}

