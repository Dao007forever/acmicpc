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

#define MAXN 100005
const LL inf = 1LL<<50;
int n, s, m;
LL dis[12][MAXN];
bool vis[MAXN];
int last[MAXN], E;
int to[MAXN << 2], prev[MAXN << 2];
LL len[MAXN << 2];
LL dp[12][1<<12];
vector<int> store;
//vector<pair<int, LL> > adj[MAXN];

void addEdge(int u, int v, LL w) {
	to[E] = v; len[E] = w; prev[E] = last[u]; last[u] = E++;
	//adj[u].PB(MP(v, w));
}

void dijkstra(int st) {
	int idx = st;
	if (st < s) st = store[st];
	else st = 0;
	for (int i = 0; i < n; i++) {
		dis[idx][i] = inf, vis[i] = false;
	}
	dis[idx][st] = 0;
	priority_queue<pair<int, int> > pq;
	pq.push(MP(0, st));
	while (!pq.empty()) {
		int u = pq.top().second; pq.pop();
		vis[u] = true;
		for (int i = last[u]; ~i; i = prev[i]) {
		//for (int i = 0; i < adj[u].size(); i++) {
			int v = to[i];
			LL w = len[i];
			//int v = adj[u][i].first;
			//LL w = adj[u][i].second;
			LL tmp = dis[idx][u] + w;
			if (!vis[v] && tmp < dis[idx][v]) {
				dis[idx][v] = tmp;
				pq.push(MP(-dis[idx][v], v));
			}
		}
	}
}

void solve() {
	for (int i = 0; i < s; i++)
		for (int j = 0; j < 1<<s; j++)
			dp[i][j] = inf;
	for (int i = 0; i < s; i++) {
		dp[i][1<<i] = dis[s][store[i]];
	}
	for (int mask = 1; mask < 1<<s; mask++) {
		for (int i = 0; i < s; i++) {
			if ((mask & (1<<i)) && dp[i][mask] != inf) {
				for (int j = 0; j < s; j++)
					if (!(mask & (1 << j))) {
						int newmask = mask | (1<<j);
						LL tmp = dp[i][mask] + dis[i][store[j]];
						if (tmp < dp[j][newmask]) {
							dp[j][newmask] = tmp;
						}
					}
			}
		}
	}
	LL ret = inf;
	for (int i = 0; i < s; i++)
		ret = min(ret, dp[i][(1<<s)-1] + dis[i][0]);
	cout << ret << endl;
}

int main(int argc, char const *argv[])
{
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		store.clear();
		E = 0;
		memset(last, -1, sizeof(last));
		scanf("%d%d", &n, &m);
		//for (int i = 0; i < n; i++) adj[i].clear();
		for (int i = 0; i < m; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			addEdge(a, b, c);
			addEdge(b, a, c);
		}
		scanf("%d", &s);
		for (int i = 0; i < s; i++) {
			int x;
			scanf("%d", &x);
			store.PB(x);
			dijkstra(i);
		}
		dijkstra(s);
		solve();
	}
	return 0;
}