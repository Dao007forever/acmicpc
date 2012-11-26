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
int n, m;
int val[MAXN], cnt[MAXN];
double d[MAXN];
bool vis[MAXN];
vector<pair<int, int> > adj[MAXN];

void addEdge(int a, int b, int c) {
	adj[a].PB(MP(b, c));
}

bool check(double t) {
	memset(d, 0, sizeof(d));
	memset(cnt, 0, sizeof(cnt));
	memset(vis, 0, sizeof(vis));
	queue<int> q;
	for (int i = 0; i < n; i++) {
		q.push(i);
		cnt[i]++;
		vis[i] = true;
	}
	while (!q.empty()) {
		int u = q.front(); q.pop();
		vis[u] = false;
		for (vector<pair<int, int> >::iterator it = adj[u].begin(); it != adj[u].end(); ++it) {
			int v = it->fi, w = it->se;
			double tmp = t * w - val[v];
			if (d[u] + tmp < d[v]) {
				d[v] = d[u] + tmp;
				if (!vis[v]) {
					vis[v] = true;
					q.push(v);
					cnt[v]++;
					if (cnt[v] > n) return true;
				}
			}
		}
	}
	return false;
}

int main() {
	freopen("in", "r", stdin);
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		cin >> val[i];
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		a--; b--;
		addEdge(a, b, c);
	}
	double l = 0, r = 10000.0, ret = -1;
	while (l + 1e-5 < r) {
		double mid = (l + r) / 2;
		if (check(mid)) {
			l = mid;
			ret = mid;
		} else r = mid;
	}
	printf("%.2f\n", ret);
	return 0;
}