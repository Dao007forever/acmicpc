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

#define maxV 505
#define maxE 5555
const int inf = 0x3f3f3f3f;
struct Edge {
	int u, v, w;
	Edge() {}
	Edge(int u, int v, int w) : u(u), v(v), w(w) {}
};
vector<Edge> es;
int n, m;
LL dis[maxV], cnt[maxV];
bool vis[maxV];
vector<pair<int, int> > adj[maxV];

bool spfa() {
	memset(dis, 0, sizeof(dis));
	memset(cnt, 0, sizeof(cnt));
	queue<int> q;
	for (int i = 1; i <= n; i++)
		q.push(i);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		vis[u] = false;
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i].first, w = adj[u][i].second;
			if (dis[u] + w < dis[v]) {
				dis[v] = dis[u] + w;
				if (!vis[v]) {
					vis[v] = true;
					q.push(v);
					cnt[v]++;
					if (cnt[v] > 50) return false;
				}
			}
		}
	}
	return true;
}

bool check(int lim) {
	for (int i = 0; i <= n; i++) adj[i].clear();
	for (int i = 0; i < m; i++) {
		int u = es[i].u, v = es[i].v, w = es[i].w;
		adj[u].PB(MP(v, w - lim));
		//cout << u << " " << v << " " << w - lim << endl;
	}
	bool flag = spfa();
	return flag;
}

int main(int argc, char const *argv[])
{
	while (~scanf("%d%d", &n, &m)) {
		es.clear();
		for (int i = 0; i < m; i++) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			es.PB(Edge(u, v, w));
		}
		int lo = 1, hi = inf;
		if (!check(lo)) {
			printf("No Solution\n");
			continue;
		}
		if (check(hi)) {
			printf("Infinite\n");
			continue;
		}
		int ret = 1;
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