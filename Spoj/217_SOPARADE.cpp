/*
 * Author : Yang Zhang
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

#define MAXN 200005
int n, m, size;
int dfn[MAXN], low[MAXN], id[MAXN];
bool vis[MAXN];
stack<int> S;
vector<int> adj[MAXN];
vector<pair<int, int> > constraint;

void Tarjan(int u, int dep) {
	dfn[u] = low[u] = dep;
	S.push(u);
	vis[u] = true;
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i];
		if (dfn[v] == -1) {
			Tarjan(v, dep + 1);
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
		} while (u != v);
	}
}

bool check() {
	for (int i = 0; i < n; i++)
		if (id[i] == id[i + n]) return false;
	return true;
}

int main() {
	freopen("in", "r", stdin);
	int Test;
	cin >> Test;
	while (Test--) {
		cin >> n >> m;
		constraint.clear();
		bool flag = true;
		for (int i = 0; i < m; i++) {
			int s;
			cin >> s;
			int pl = -1, ph = -1;
			while (s--) {
				int tmp;
				cin >> tmp;
				tmp--;
				if (tmp & 1) {
					if (ph == -1)
						ph = tmp;
					else {
						if (ph == -2) {
							flag = false;
						} else {
							constraint.PB(MP(ph, tmp));
							ph = -2;
						}
					}
				} else {
					if (pl == -1)
						pl = tmp;
					else {
						if (pl == -2) {
							flag = false;
						} else {
							constraint.PB(MP(pl, tmp));
							pl = -2;
						}
					}
				}
			}
		}

		if (!flag) {
			cout << "rejected" << endl;
			continue;
		}
		for (int i = 0; i < n + n; i++)
			adj[i].clear();

		for (int i = 0; i < n - 1; i++) {
			adj[i].PB(i + n + 1);
			adj[i + 1].PB(i + n);
			//cout << i << " " << i + n + 1 << endl;
			//cout << i + 1 << " " << i + n << endl;
		}

		for (int i = 0; i < constraint.size(); i++) {
			int a = constraint[i].first, b = constraint[i].second;
			adj[a].PB(b + n);
			adj[a + n].PB(b);
			adj[b].PB(a + n);
			adj[b + n].PB(a);
			//cout << a << " " << b + n << endl;
			//cout << a + n << " " << b << endl;
			//cout << b << " " << a + n << endl;
			//cout << b + n << " " << a << endl;
		}
		size = 0;
		memset(id, 0, sizeof(id));
		memset(dfn, -1, sizeof(dfn));
		memset(vis, false, sizeof(false));
		for (int i = 0; i < n + n; i++)
			if (dfn[i] == -1) Tarjan(i, 1);
		if (check()) cout << "approved" << endl;
		else cout << "rejected" << endl;
	}
	return 0;
}
