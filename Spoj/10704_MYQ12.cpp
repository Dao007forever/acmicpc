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

const int maxV = 505;
const int maxE = 50005;
const int inf = 0x3f3f3f3f;
const int mod = 1000000007;
int n, m;
int S, D;
vector<pair<int, int> > adj[maxV];
int dp[maxV], pt[maxV];
bool vis[maxV];
LL g[maxV];
int edgeA[maxE], edgeB[maxE], edgeC[maxE];
int dS[maxV], dT[maxV];

void init() {
	for (int i = 0; i < n; i++) adj[i].clear();
}

void dijkstra(int st, int d[]) {
	vector<bool> vst(n);
	for (int i = 0; i < n; i++) {
		d[i] = inf; vst[i] = false;
	}
	priority_queue<pair<int, int> > pq;
	d[st] = 0;
	pq.push(MP(0, st));
	while (!pq.empty()) {
		int u = pq.top().second; pq.pop();
		vst[u] = true;
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i].first, tmp = d[u] + adj[u][i].second;
			if (!vst[v] && tmp < d[v]) {
				d[v] = tmp;
				pq.push(MP(-tmp, v));
			}
		}
	}
}

void solve() {
	for (int i = 0; i < n; i++) {
		dp[i] = inf; g[i] = 1; pt[i] = inf; vis[i] = false;
	}
	queue<int> q;
	dp[S] = 0;
	g[S] = 1;
	pt[S] = 1;
	q.push(S);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		vis[u] = false;
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i].first, tmp = dp[u] + adj[u][i].second;
			if (tmp < dp[v]) {
				dp[v] = tmp;
				pt[v] = pt[u] + 1;
				g[v] = g[u];
				if (!vis[v]) {
					vis[v] = true;
					q.push(v);
				}
			} else if (tmp == dp[v] && pt[u] + 1 < pt[v]) {
				pt[v] = pt[u] + 1;
				g[v] = g[u];
				if (!vis[v]) {
					vis[v] =true;
					q.push(v);
				}
			} else if (tmp == dp[v] && pt[u] + 1 == pt[v]) {
				g[v] = (g[v] + g[u]) % mod;
				if (!vis[v]) {
					vis[v] = true;
					q.push(v);
				}
			}
		}
	}
}

int main(int argc, char const *argv[])
{
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		init();
		scanf("%d%d", &n, &m);
		for (int i = 0; i < m; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			a--; b--;
			edgeA[i] = a; edgeB[i] = b; edgeC[i] = c;
			adj[a].PB(MP(b, c));
		}
		scanf("%d%d", &S, &D);
		S--; D--;
		dijkstra(S, dS);
		if (dS[D] == inf) {
			puts("-1");
			continue;
		}
		init();
		for (int i = 0; i < m; i++) {
			int a = edgeA[i], b = edgeB[i], c = edgeC[i];
			adj[b].PB(MP(a, c));
		}
		dijkstra(D, dT);
		init();
		for (int i = 0; i < m; i++) {
			int a = edgeA[i], b = edgeB[i], c = edgeC[i];
			if (dS[a] + c + dT[b] == dS[D]) continue;
			//cout << a << " " << b << " " << c << endl;
			adj[a].PB(MP(b, c));
		}
		solve();
		if (dp[D] == inf) {
			puts("-1");
		} else {
			printf("%d %d %lld\n", dp[D], pt[D], g[D]);
		}
	}
	return 0;
}