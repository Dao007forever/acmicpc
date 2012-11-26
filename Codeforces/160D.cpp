/*
 *  并查集 + 求桥
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

#define maxn 100005
struct Edge {
	int x, y, w, id;
	bool operator < (const Edge &A) const {
		return w < A.w;
	}
}edge[maxn];
struct DisJointSet{
	int rank[maxn], parent[maxn];

	void init(int n) {
		for (int i = 0; i < n; i++) {
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
}ufset;
int V;
bool visit[maxn];
vector<pair<int, int> > graph[maxn];
map<int, int> mp;
int dfn[maxn], low[maxn], tag[maxn];

bool cmp_id(const Edge &A, const Edge &B) {
	return A.id < B.id;
}

void Tarjan(int fa, int u, int dep) {
	dfn[u] = low[u] = dep;
	for (int i = 0; i < graph[u].size(); i++) {
		int v = graph[u][i].first;
		int id = graph[u][i].second;
		if (dfn[v] == -1) {
			visit[id] = true;//因为是无向边，所以这条边只访问一次
			Tarjan(u, v, dep + 1);
			low[u] = min(low[u], low[v]);
			if (low[v] > dfn[u]) tag[id] = 1;//编号为id的这条边为割边
		} else if (!visit[id]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
}

void Bridge() {
	for (int i = 0; i < V; i++)
		dfn[i] = -1;
	for (int i = 0; i < V; i++)
		if (dfn[i] == -1) Tarjan(-1, i, 0);
}

int main() {
	freopen("in", "r", stdin);
	memset(tag, -1, sizeof(tag));
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		cin >> edge[i].x >> edge[i].y >> edge[i].w;
		edge[i].id = i;
	}
	sort(edge, edge + m);
	int l = 0, r;
	ufset.init(n);
	while (l < m) {
		r = l;
		while (r < m && edge[r].w == edge[l].w) {
			r++;
		}
		mp.clear();
		for (int i = l; i < r; i++) {
			int fx = ufset.Find(edge[i].x), fy = ufset.Find(edge[i].y);
			if (fx == fy) {
				tag[edge[i].id] = 0;
			} else {
				mp[fx] = mp[fy] = 0;
			}
		}
		//无向图求割边
		V = 0;
		for (map<int, int>::iterator it = mp.begin(); it != mp.end(); it++) {
			it->second = V;
			V++;
		}
		for (int i = 0; i < V; i++)
			graph[i].clear();
		for (int i = l; i < r; i++) {
			int fx = ufset.Find(edge[i].x), fy = ufset.Find(edge[i].y);
			if (fx == fy) continue;
			int a = mp[fx], b = mp[fy];
			graph[a].push_back(make_pair(b, edge[i].id));
			graph[b].push_back(make_pair(a, edge[i].id));
		}
		Bridge();
		for (int i = l; i < r; i++)
			ufset.Union(edge[i].x, edge[i].y);

		l = r;
	}
	sort(edge, edge + m, cmp_id);
	for (int i = 0; i < m; i++) {
		if (tag[i] == 1) {
			cout << "any" << endl;
		} else if (tag[i] == 0) {
			cout << "none" << endl;
		} else {
			cout << "at least one" << endl;
		}
	}
	return 0;
}
