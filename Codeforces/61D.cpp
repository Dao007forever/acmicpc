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

#define MAXN 100005
const long long inf = 1LL << 60;
int n;
long long dist[MAXN];
bool vis[MAXN];
vector<pair<int, int> > adj[MAXN];

void spfa() {
	for (int i = 1; i <= n; i++) {
		dist[i] = inf;
		vis[i] = false;
	}
	vis[1] = true;
	dist[1] = 0;
	queue<int> Q;
	Q.push(1);
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		vis[u] = false;
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i].first, w = adj[u][i].second;
			if (dist[u] + w < dist[v]) {
				dist[v] = dist[u] + w;
				if (!vis[v]) {
					vis[v] = true;
					Q.push(v);
				}
			}
		}
	}
}

int main() {
	long long ret = 0;
	cin >> n;
	for (int i = 1; i < n; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back(make_pair(v, w));
		adj[v].push_back(make_pair(u, w));
		ret += w;
	}
	spfa();
	long long Max = 0;
	for (int i = 2; i <= n; i++)
		Max = max(Max, dist[i]);
	ret <<= 1;
	ret -= Max;
	cout << ret << endl;
	return 0;
}
