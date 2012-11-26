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

#define MAXN 1005
const int inf = 0x3f3f3f3f;
int n, m, st, ed;
int dis[MAXN][2], cnt[MAXN][2];
bool vis[MAXN][2];
vector<pair<int, int> > adj[MAXN];
struct node {
	int d, u, flag;
	node() {}
	node(int u, int flag, int d) : u(u), flag(flag), d(d) {}
	bool operator < (const node &p) const {
		return d > p.d;
	}
};

/*void dijkstra() {
	for (int i = 0; i < n; i++) {
		dis[i][0] = dis[i][1] = inf;
		vis[i][0] = vis[i][1] = false;
		cnt[i][0] = cnt[i][1] = 0;
	}
	dis[st][0] = 0;
	cnt[st][0] = 1;
	priority_queue<node> pq;
	pq.push(node(st, 0, 0));
	while (!pq.empty()) {
		node cur = pq.top(); pq.pop();
		int u = cur.u, flag = cur.flag;
		if (vis[u][flag]) continue;
		vis[u][flag] = true;
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i].first, tmp = dis[u][flag] + adj[u][i].second;
			if (tmp < dis[v][0]) {
				if (dis[v][0] != inf) {
					dis[v][1] = dis[v][0];
					cnt[v][1] = cnt[v][0];
					pq.push(node(v, 1, dis[v][1]));
				}
				dis[v][0] = tmp;
				cnt[v][0] = cnt[u][flag];
				pq.push(node(v, 0, dis[v][0]));
			} else if (tmp == dis[v][0]) {
				cnt[v][0] += cnt[u][flag];
			} else if (tmp < dis[v][1]) {
				dis[v][1] = tmp;
				cnt[v][1] = cnt[u][flag];
				pq.push(node(v, 1, dis[v][1]));
			} else if (tmp == dis[v][1]) {
				cnt[v][1] += cnt[u][flag];
			}
		}
	}
}*/

void dijkstra() {
	for (int i = 0; i < n; i++) {
		dis[i][0] = dis[i][1] = inf;
		vis[i][0] = vis[i][1] = false;
		cnt[i][0] = cnt[i][1] = 0;
	}
	dis[st][0] = 0;
	cnt[st][0] = 1;
	for (int i = 0; i < 2*n; i++) {
		int Min = inf, u = -1, flag;
		for (int j = 0; j < n; j++) {
			if (!vis[j][0] && dis[j][0] < Min) {
				u = j; flag = 0; Min = dis[j][0];
			} else if (!vis[j][1] && dis[j][1] < Min) {
				u = j; flag = 1; Min = dis[j][1];
			}
		}
		if (u == -1) break;
		vis[u][flag] = true;
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i].first, tmp = dis[u][flag] + adj[u][i].second;
			if (tmp < dis[v][0]) {
				dis[v][1] = dis[v][0];
				cnt[v][1] = cnt[v][0];
				dis[v][0] = tmp;
				cnt[v][0] = cnt[u][flag];
			} else if (tmp == dis[v][0]) {
				cnt[v][0] += cnt[u][flag];
			} else if (tmp < dis[v][1]) {
				dis[v][1] = tmp;
				cnt[v][1] = cnt[u][flag];
			} else if (tmp == dis[v][1]) {
				cnt[v][1] += cnt[u][flag];
			}
		}
	}
}

int main(int argc, char const *argv[])
{
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; i++) adj[i].clear();
		for (int i = 0; i < m; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			a--; b--;
			adj[a].PB(MP(b, c));
		}
		scanf("%d%d", &st, &ed);
		st--; ed--;
		dijkstra();
		int d = dis[ed][0], ret = cnt[ed][0];
		if (d + 1 == dis[ed][1]) ret += cnt[ed][1];
		printf("%d\n", ret);
	}
	return 0;
}