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

#define MAXN 1005
int N, M, ret;
vector<int> adj[MAXN], revadj[MAXN], ans[MAXN];
int outdeg[MAXN];
bool vis[MAXN][MAXN];

void solve() {
	queue<int> Q;
	for (int i = 1; i <= N; i++)
		if (outdeg[i] == 0) Q.push(i);
	while (!Q.empty()) {
		int u = Q.front(); Q.pop();
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i];
			if (!vis[u][v]) {
				ans[u].PB(v);
				ret++;
				vis[u][v] = true;
			}
		}

		//update transitive
		for (int i = 0; i < revadj[u].size(); i++) {
			int v = revadj[u][i];
			for (int i = 1; i <= N; i++)
				if (vis[u][i]) vis[v][i] = true;
			outdeg[v]--;
			if (outdeg[v] == 0) Q.push(v);
		}
	}
}

int main() {
	freopen("in", "r", stdin);
	scanf("%d%d", &N, &M);
	for (int i = 0; i < M; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a].PB(b); revadj[b].PB(a);
		outdeg[a]++;
	}

	solve();

	printf("%d\n", ret);
	for (int i = 1; i <= N; i++)
		for (int j = 0; j < ans[i].size(); j++)
			printf("%d %d\n", i, ans[i][j]);
	return 0;
}
