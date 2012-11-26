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

#define MAXN 105
int N, M;
int ind[MAXN], ans[MAXN];
vector<int> adj[MAXN], topo;

bool toposort()
{
	queue<int> Q;
	for (int cnt = 0; cnt < N;) {
		int k = 0;
		for (int i = 1; i <= N; i++)
			if (ind[i] == 0) {
				Q.push(i);
				k++;
			}
		if (k == 0) {
			return false;
		}
		while (!Q.empty()) {
			int u = Q.front();
			Q.pop();
			topo.push_back(u);
			ind[u] = -1;
			for (int i = 0; i < adj[u].size(); i++)
				ind[adj[u][i]]--;
		}
		cnt += k;
	}
	return true;
}

int main()
{
	freopen("in", "r", stdin);
	cin >> N >> M;
	while (M--) {
		int a, b;
		cin >> a >> b;
		adj[b].push_back(a);
		ind[a]++;
	}
	if (!toposort()) {
		puts("No solution");
	} else {
		for (int i = 0; i < N; i++)
			ans[topo[i]] = N - i;
		for (int i = 1; i <= N; i++)
			printf("%d ", ans[i]);
	}
	return 0;
}
