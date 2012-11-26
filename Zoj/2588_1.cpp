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

#define maxn 100005
int N, M;
bool visit[maxn];
vector<pair<int, int> > graph[maxn];
int dfn[maxn], low[maxn], parent[maxn], tag[maxn];
int ret;

void Tarjan(int fa, int u, int dep) {
	parent[u] = fa;
	dfn[u] = low[u] = dep;
	for (int i = 0; i < graph[u].size(); i++) {
		int v = graph[u][i].first;
		int id = graph[u][i].second;
		if (dfn[v] == -1) {
			visit[id] = true;
			Tarjan(u, v, dep + 1);
			low[u] = min(low[u], low[v]);
		} else if (!visit[id]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
}

void Bridge() {
	for (int i = 0; i < N; i++)
		parent[i] = dfn[i] = -1;
	for (int i = 0; i < N; i++)
		if (dfn[i] == -1) Tarjan(-1, i, 0);
	for (int a = 0; a < N; a++) {
		for (int i = 0; i < graph[a].size(); i++) {
			int b = graph[a][i].first;
			int id = graph[a][i].second;
			if (b == parent[a] && low[a] == dfn[a]) {
				tag[id] = 1;
				ret++;
			}
		}
	}
}

vector<int> ans;
int main() {
	freopen("in", "r", stdin);
	int Test;
	cin >> Test;
	while (Test--) {
		ret = 0;
		memset(tag, 0, sizeof(tag));
		cin >> N >> M;
		for (int i = 0; i < N; i++)
			graph[i].clear();
		for (int i = 0; i < M; i++) {
			int a, b;
			cin >> a >> b;
			a--; b--;
			graph[a].push_back(make_pair(b, i));
			graph[b].push_back(make_pair(a, i));
		}
		Bridge();

		cout << ret << endl;
		for (int i = 0, k = ret; i < M; i++)
			if (tag[i]) {
				cout << i + 1;
				if (--k) printf(" ");
			}
		if (ret) cout << endl;
		if (Test) cout << endl;
	}
	return 0;
}
