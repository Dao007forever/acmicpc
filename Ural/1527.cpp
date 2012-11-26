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

#define MAXM 10005
#define MAXN 105
const int inf = 1000000000;
bool vis[MAXN][MAXM];
int dis[MAXN][MAXM], pre[MAXN][MAXM], preu[MAXN][MAXM], prez[MAXN][MAXM];
struct node {
	int u, z, cost;
	node() {}
	node(int _u, int _z, int _cost) {
		u = _u; z = _z; cost = _cost;
	}
	bool operator < (const node it) const {
		return cost > it.cost;
	}
};
struct Vertex {
	int v, z, t, h, id;
	Vertex() {}
	Vertex(int _v, int _z, int _t, int _h, int _id) {
		v = _v; z = _z; t = _t; h = _h; id = _id;
	}
};
int n, m, s, t, money, maxtime;
vector<Vertex> adj[MAXN];
vector<int> ans;

void recur(int u, int z) {
	if (pre[u][z] == -1) return;
	recur(preu[u][z], prez[u][z]);
	ans.PB(pre[u][z]);
}

/*int spfa(int limit) {
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= money; j++) {
			dis[i][j] = inf;
			vis[i][j] = false;
		 }
	}
	dis[s][0] = 0;
	vis[s][0] = true;
	pre[s][0] = -1;
	queue<node> Q;
	Q.push(node(s, 0));
	while (!Q.empty()) {
		node cur = Q.front();
		Q.pop();
		int u = cur.u;
		vis[u][cur.z] = false;
		if (u == t) {
			ans.clear();
			recur(cur.u, cur.z);
			return dis[cur.u][cur.z];
		}
		for (int i = 0; i < adj[u].size(); i++) {
			if (limit < adj[u][i].h) continue;
			int v = adj[u][i].v, z = adj[u][i].z, t = adj[u][i].t, id = adj[u][i].id;
			if (cur.z + z <= money && dis[v][cur.z + z] > dis[u][cur.z] + t) {
				dis[v][cur.z + z] = dis[u][cur.z] + t;
				pre[v][cur.z + z] = id;
				preu[v][cur.z + z] = u; prez[v][cur.z + z] = cur.z;
				if (!vis[v][cur.z + z]) {
					vis[v][cur.z + z] = true;
					Q.push(node(v, cur.z + z));
				}
			}
		}
	}
	return inf;
}*/

int dijk(int limit) {
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= money; j++)
			dis[i][j] = inf;
	node s1, s2;
	priority_queue<node> Q;
	s1.u = s; s1.z = 0; s1.cost = 0;
	dis[s][0] = 0; pre[s][0] = -1;
	Q.push(s1);
	while (!Q.empty()) {
		s1 = Q.top();
		Q.pop();
		if (s1.u == t) {
			ans.clear();
			recur(s1.u, s1.z);
			return s1.cost;
		}
		int u = s1.u;
		for (int i = 0; i < adj[u].size(); i++) {
			if (limit < adj[u][i].h) continue;
			s2.u = adj[u][i].v;
			s2.z = s1.z + adj[u][i].z;
			s2.cost = s1.cost + adj[u][i].t;
			if (s2.z <= money && dis[s2.u][s2.z] > s2.cost) {
				dis[s2.u][s2.z] = s2.cost;
				pre[s2.u][s2.z] = adj[u][i].id;
				preu[s2.u][s2.z] = s1.u;
				prez[s2.u][s2.z] = s1.z;
				Q.push(s2);
			}
		}
	}
	return inf;
}

int main() {
	freopen("in", "r", stdin);
	scanf("%d%d%d%d", &n, &m, &s, &t);
	scanf("%d%d", &money, &maxtime);
	money = min(money, m);
	int l = 0, r = 0;
	for (int i = 1; i <= m; i++) {
		int x, y, z, t, h;
		scanf("%d%d%d%d%d", &x, &y, &z, &t, &h);
		adj[x].PB(Vertex(y, z, t, h, i));
		r = max(r, h);
	}
	int ret = -1;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (dijk(mid) <= maxtime) {
			ret = mid;
			r = mid - 1;
		} else l = mid + 1;
	}
	if (ret == -1) {
		printf("-1\n");
		return 0;
	}
	dijk(ret);
	printf("%d\n", ret);
	printf("%d\n", ans.size());
	for (int i = 0; i < ans.size(); i++)
		printf("%d%c", ans[i], i == ans.size() - 1 ? '\n' : ' ');
	return 0;
}
