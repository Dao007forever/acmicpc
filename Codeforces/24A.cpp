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

int n, sum, ret;
int adj[111][111];
bool vis[111];

int dfs(int u) {
	vis[u] = true;
	for (int i = 0; i < n; i++)
		if (!vis[i] && adj[u][i] != -1) {
			ret += adj[u][i];
			return dfs(i);
		}
	return u;
}

int main() {
	cin >> n;
	ret = 0;
	memset(adj, -1, sizeof(adj));
	for (int i = 0; i < n; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		a--; b--;
		adj[a][b] = 0;
		adj[b][a] = c;
		sum += c;
	}
	int tmp = dfs(0);
	ret += adj[tmp][0];
	cout << min(ret, sum - ret) << endl;
	return 0;
}
