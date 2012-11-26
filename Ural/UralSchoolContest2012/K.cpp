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

#define maxV 10005
const int inf = 0x3f3f3f3f;
int n, m, s, t;
vector<pair<int, int > > adj[maxV];
bool vis[maxV][2];
int dp[maxV][2];

int main(int argc, char const *argv[])
{
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].PB(MP(b, 0));
		adj[b].PB(MP(a, 1));
	}
	cin >> s >> t;
	for (int i = 1; i <= n; i++) {
		dp[i][0] = dp[i][1] = inf;
	}
	queue<pair<int, int> > q;
	dp[s][0] = dp[s][1] = 0;
	q.push(MP(s, 0));
	q.push(MP(s, 1));
	while (!q.empty()) {
		pair<int, int> cur = q.front(); q.pop();
		int u = cur.first, type = cur.second;
		vis[u][type] = false;
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i].first, newt = adj[u][i].second;
			if (dp[u][type] + (type != newt) < dp[v][newt]) {
				dp[v][newt] = dp[u][type] + (type != newt);
				if (!vis[v][newt]) {
					vis[v][newt] = true;
					q.push(MP(v, newt));
				}
			}
		}
	}
	int ret = min(dp[t][0], dp[t][1]);
	cout << ret << endl;
	return 0;
}