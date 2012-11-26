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
/*------------#include omitted-----------*/
#define MAXN 100005
const LL inf = 1LL << 60;
map<string, int> mp;
int disS[MAXN], disT[MAXN];
struct Graph {
	int n;
	vector<pair<int, int> > adj[MAXN];
	LL dis[MAXN];
	bool vst[MAXN];

	void init(int n) {
		this->n = n;
		for (int i = 0; i <= n; i++)
			adj[i].clear();
	}

	void addEdge(int u, int v, LL w) {
		adj[u].PB(MP(v, w));
	}

	void dijkstra(int st) {
		for (int i = 0; i <= n; i++) {
			dis[i] = inf;
			vst[i] = false;
		}
		dis[st] = 0; vst[st] = true;
		priority_queue<pair<int, int> > Q;
		Q.push(MP(0, st));
		while (!Q.empty()) {
			pair<int, int> cur = Q.top(); Q.pop();
			int u = cur.second;
			for (int i = 0; i < adj[u].size(); i++) {
				int v = adj[u][i].first, w = adj[u][i].second;
				if (!vst[v] && dis[u] + w < dis[v]) {
					vst[v] = true;
					dis[v] = dis[u] + w;
					Q.push(MP(-dis[v], v));
				}
			}
		}
	}
}gS, gT;

struct Edge {
	int u, v, w;

	Edge(int _u, int _v, int _w) {
		u = _u; v = _v; w = _w;
	}
};
vector<Edge> edge;
int main() {
	int n, m;
	while (~scanf("%d%d", &n, &m)) {
		mp.clear();
		edge.clear();
		char s1[15], s2[15];
		int u, v, len;
		int cnt = 1;
		gS.init(n); gT.init(n);
		for (int i = 0; i < m; i++) {
			scanf("%s %s %d", s1, s2, &len);
			string name1(s1), name2(s2);
			if (mp.find(name1) == mp.end()) {
				mp[name1] = u = cnt++;
			} else u = mp[name1];
			if (mp.find(name2) == mp.end()) {
				mp[name2] = v = cnt++;
			} else v = mp[name2];
			gS.addEdge(u, v, len); gT.addEdge(v, u, len);
			edge.PB(Edge(u, v, len));
		}
		scanf("%s %s", s1, s2);
		string nameS(s1), nameT(s2);
		int S = mp[nameS], T = mp[nameT];
		if (!S || !T) {
			cout << -1 << endl;
			continue;
		}
		if (S == T) {
			cout << 0 << endl;
		}
		gS.dijkstra(S);
		gT.dijkstra(T);
		if (gS.dis[T] == inf) {
			cout << -1 << endl;
			continue;
		}
		LL ret = inf;
		for (int i = 0; i < m; i++) {
			LL tmp = gS.dis[edge[i].u] + edge[i].w / 2 + gT.dis[edge[i].v];
			if (tmp < ret)
				ret = tmp;
		}
		if (ret == inf) ret = -1;
		cout << ret << endl;
	}
	return 0;
}
