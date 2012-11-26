/*
 * Author : Yang Zhang
 */
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

int n;
map<int, vector<int> > adj;
map<int, vector<int> >::iterator it;

void dfs(int u, int fa) {
	cout << u << " ";
	for (int i = 0; i < adj[u].size(); i++) {
		if (adj[u][i] != fa)
			dfs(adj[u][i], u);
	}
}
int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].PB(b);
		adj[b].PB(a);
	}

	for (it = adj.begin(); it != adj.end(); it++) {
		if (it->second.size() == 1) {
			dfs(it->first, -1);
			return 0;
		}
	}
}
