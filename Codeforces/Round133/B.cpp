/*
 * Author: Yang Zhang
 * Created Time: Sat 18 Aug 2012 12:04:14 PM UTC
 * File Name: B.cpp
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

#define maxn 105
int n, m;
vector<int> adj[maxn];
int col[maxn];
bool flag;

void dfs(int u, int color) {
	if (!flag) return;
	if (col[u]) {
		if (col[u] != color) flag = false;
		return;
	}
	col[u] = color;
	for (int i = 0; i < adj[u].size(); i++)
		dfs(adj[u][i], 3 - color);
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].PB(b); adj[b].PB(a);
	}
	int ret = 0;
	for (int i = 1; i <= n; i++)
		if (!col[i]) {
			flag = true;
			dfs(i, 1);
			if (!flag) ret++;
		}
	if ((n - ret) & 1) ret++;
	cout << ret << endl;
	return 0;
}

