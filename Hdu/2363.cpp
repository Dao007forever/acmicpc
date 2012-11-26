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

#define MAXN 105
const int inf = 0x3f3f3f3f;
int n, m;
int height[MAXN];
int ret, Dist;
int adj[MAXN][MAXN];

int check(int minH, int maxH) {
	static int dis[MAXN];
	static bool vis[MAXN];
	for (int i = 0; i < n; i++) {
		dis[i] = inf;
		if (height[i] < minH || height[i] > maxH) vis[i] = true;
		else vis[i] = false;
	}
	if (vis[0] || vis[n - 1]) return inf;
	dis[0] = 0;
	for (int i = 0; i < n; i++) {
		int k = -1, Min = inf;
		for (int j = 0; j < n; j++) {
			if (!vis[j] && dis[j] < Min) {
				Min = dis[j];
				k = j;
			}
		}
		if (k == -1) break;
		vis[k] = true;
		for (int j = 0; j < n; j++) {
			if (!vis[j] && dis[k] + adj[k][j] < dis[j])
				dis[j] = dis[k] + adj[k][j];
		}
	}
	return dis[n - 1];
}

void solve(int minH, int maxH) {
	int lo = minH, hi = maxH, ans = -1, minD;
	while (lo <= hi) {
		int mid = (lo + hi) >> 1;
		int D;
		if ((D = check(minH, mid)) != inf) {
			ans = mid;
			minD = D;
			hi = mid - 1;
		} else lo = mid + 1;
	}
	if (ans != -1) {
		if (ans - minH < ret) {
			ret = ans - minH;
			Dist = minD;
		} else if (ans - minH == ret && minD < Dist) {
			Dist = minD;
		}
	}
/*	int ans = maxH;
	int minD = check(minH, maxH);
	if (minD != inf) {
		if (ans - minH < ret) {
			ret = ans - minH;
			Dist = minD;
		} else if (ans - minH == ret && minD < Dist) {
			Dist = minD;
		}
	}*/
}

int main(int argc, char const *argv[])
{
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				adj[i][j] = i == j ? 0 : inf;
		int maxH = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d", &height[i]);
			maxH = max(maxH, height[i]);
		}
		for (int i = 0; i < m; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			a--; b--;
			adj[a][b] = adj[b][a] = min(adj[a][b], c);
		}
		ret = inf; Dist = inf;
		for (int i = 0; i < n; i++) {
			solve(height[i], maxH);
		}
		/*for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (height[i] < height[j]) {
					solve(height[i], height[j]);
				}*/
		printf("%d %d\n", ret, Dist);
	}
	return 0;
}