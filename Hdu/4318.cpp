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

#define MAXN 50005
const double inf = 1e50;
int n, s, t;
double dis[MAXN];
bool vis[MAXN];
vector<pair<int, int> > adj[MAXN];
double energy;

bool dijkstra() {
	for (int i = 0; i < n; i++) {
		dis[i] = inf, vis[i] = false;
	}
	dis[s] = 0;
	priority_queue<pair<double, int> > pq;
	pq.push(MP(0, s));
	while (!pq.empty()) {
		int u = pq.top().second; pq.pop();
		vis[u] = true;
		if (u == t) return true;
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i].first, w = adj[u][i].second;
			if (!vis[v]) {
				double tmp = dis[u] + (energy - dis[u]) * w / 100.0;
				if (tmp < dis[v]) {
					dis[v] = tmp;
					pq.push(MP(-dis[v], v));
				}
			}
		}
	}
	return false;
}

int main(int argc, char const *argv[])
{
	while (~scanf("%d", &n)) {
		for (int i = 0; i < n; i++) adj[i].clear();
		for (int i = 0; i < n; i++) {
			int k, a, b;
			scanf("%d", &k);
			while (k--) {
				scanf("%d%d", &a, &b);
				a--;
				adj[i].PB(MP(a, b));
			}
		}
		scanf("%d%d%lf", &s, &t, &energy);
		s--; t--;
		bool reach = dijkstra();
		if (!reach) {
			puts("IMPOSSIBLE!");
		} else {
			printf("%.2f\n", dis[t]);
		}
	}
	return 0;
}