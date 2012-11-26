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

#define MAXN 5005
const int inf = 0x3f3f3f3f;
int n, m;
vector<pair<int, int> > adj[MAXN];

void addEdge(int u, int v, int w) {
	adj[u].PB(MP(v, w));
}

void dijkstra(int st, vector<int> &d) {
	vector<bool> vis(n);
	for (int i = 0; i < n; i++) d[i] = inf;
	d[st] = 0;
	priority_queue<pair<int, int> > pq;
	pq.push(MP(0, st));
	while (!pq.empty()) {
		int u = pq.top().second; pq.pop();
		vis[u] = true;
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i].first, w = adj[u][i].second;
			if (!vis[v] && d[u] + w < d[v]) {
				d[v] = d[u] + w;
				pq.push(MP(-d[v], v));
			}
		}
	}
}

int main(int argc, char const *argv[])
{
	vector<pair<int, int> > edge;
	vector<int> val;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		u--; v--;
		edge.PB(MP(u, v));
		val.PB(w);
		addEdge(u, v, w);
		addEdge(v, u, w);
	}
	vector<int> dS(n), dT(n);
	dijkstra(0, dS);
	dijkstra(n - 1, dT);
	int ret = inf;
	for (int i = 0; i < edge.size(); i++) {
		int u = edge[i].first, v = edge[i].second;
		int tmp = dS[u] + val[i] + dT[v];
		if (tmp > dS[n - 1]) {
			ret = min(ret, tmp);
		}
		tmp = dS[v] + val[i] + dT[u];
		if (tmp > dS[n - 1]) {
			ret = min(ret, tmp);
		}
	}
	if (ret == inf) while (1);
	printf("%d\n", ret);
	return 0;
}