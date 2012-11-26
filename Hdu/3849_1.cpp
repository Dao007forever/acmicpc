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
struct Edge {
	char a[22], b[22];
}edge[maxn];
int N, M, ret;
bool visit[maxn];
int dfn[maxn], low[maxn], tag[maxn];
map<string, int> mp;
vector<pair<int, int> > graph[maxn];
struct DisJointSet{
	int rank[maxn], parent[maxn];

	void init(int n) {
		for (int i = 0; i < maxn; i++) {
			rank[i] = 0;
			parent[i] = i;
		} 
	}

	int Find(int x) {
		if (parent[x] == x) return x;
		return parent[x] = Find(parent[x]);
	}

	void Union(int x, int y) {
		x = Find(x);
		y = Find(y);

		if (x == y) return;
		
		if (rank[x] >= rank[y]) {
			parent[y] = x;
			if (rank[x] == rank[y])
				rank[x]++;
		}
		else {
			parent[x] = y;
		}
	}

	int count(int n) {
		int ret = 0;
		for (int i = 0; i < n; i++)
			if (parent[i] == i) ret++;
		return ret;
	}
}DJS;

void Tarjan(int fa, int u, int dep) {
	dfn[u] = low[u] = dep;
	for (int i = 0; i < graph[u].size(); i++) {
		int v = graph[u][i].first;
		int id = graph[u][i].second;
		if (dfn[v] == -1) {
			visit[id] = true;
			Tarjan(u, v, dep + 1);
			low[u] = min(low[u], low[v]);
			if (low[v] > dfn[u]) {
				ret++;
				tag[id] = 1;
			}
		} else if (!visit[id]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
}

void Bridge() {
	for (int i = 0; i < N; i++)
		dfn[i] = -1;
	for (int i = 0; i < N; i++)
		if (dfn[i] == -1) Tarjan(-1, i, 0);
}

int main() {
	freopen("in", "r", stdin);
	int Test;
	cin >> Test;
	while (Test--) {
		memset(tag, 0, sizeof(tag));
		memset(visit, 0, sizeof(visit));
		cin >> N >> M;
		mp.clear();
		DJS.init(N);
		ret = 0;
		for (int i = 0; i < N; i++)
			graph[i].clear();
		int V = 0;
		for (int i = 0; i < M; i++) {
			scanf("%s %s", edge[i].a, edge[i].b);
			int u, v;
			string s;
			s.assign(edge[i].a);
			if (mp.find(s) == mp.end()) {
				mp[s] = V++;
			}
			u = mp[s];
			s.assign(edge[i].b);
			if (mp.find(s) == mp.end()) {
				mp[s] = V++;
			}
			v = mp[s];
			if (DJS.Find(u) != DJS.Find(v)) {
				DJS.Union(u, v);
			}
			graph[u].push_back(make_pair(v, i));
			graph[v].push_back(make_pair(u, i));
		}
		if (DJS.count(N) > 1) {
			cout << 0 << endl;
			continue;
		}
		Bridge();
		cout << ret << endl;
		for (int i = 0; i < M; i++)
			if (tag[i]) {
				printf("%s %s\n", edge[i].a, edge[i].b);
			}
	}
	return 0;
}
