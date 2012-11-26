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

#define MAXN 500005
int n, m;
vector<int> adj[MAXN];
set<int> ms;
vector<int> ans[MAXN];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a].PB(b); adj[b].PB(a);
	}
	for (int i = 1; i <= n; i++)
		sort(adj[i].begin(), adj[i].end());
	for (int i = 1; i <= n; i++) {
		ms.insert(i);
	}
	int ret = 0, now = 0;
	vector<int> p;
	queue<int> Q;
	while (!ms.empty()) {
		int cur = *ms.begin();
		while (!Q.empty()) Q.pop();
		Q.push(cur);
		ms.erase(cur);
		ans[ret].clear();
		while (!Q.empty()) {
			p.clear();
			now++;
			int u = Q.front();
			Q.pop();
			ans[ret].PB(u);
			for (set<int>::iterator it = ms.begin(); it != ms.end(); it++) {
				int v = *it;
				if (!binary_search(adj[u].begin(), adj[u].end(), v)) {
					Q.push(v);
					p.PB(v);
				}
			}
			for (int i = 0; i < p.size(); i++)
				ms.erase(p[i]);
		}
		ret++;
	}
	printf("%d\n", ret);
	for (int i = 0; i < ret; i++) {
		printf("%d", ans[i].size());
		for (int j = 0; j < ans[i].size(); j++)
			printf(" %d", ans[i][j]);
		puts("");
	}
	return 0;
}

