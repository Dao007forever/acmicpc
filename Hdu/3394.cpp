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
/*------------#include omitted-----------*/

#define MAXN 20005
#define MAXM 200005
struct Graph {
	vector<pair<int, int> > adj[MAXN];
	int dfn[MAXN], low[MAXN];
	bool vst[MAXN];
	bool visit[MAXM];
	int N, M, size, depth;
	int ret1, ret2;
	stack<int> S;
	vector<int> block;

	void init(int n) {
		N = n;
		memset(vst, 0, sizeof(vst));
		memset(visit, 0, sizeof(visit));
		for (int i = 0; i < n; i++)
			adj[i].clear();
	}

	void addEdge(int u, int v, int id) {
		adj[u].PB(MP(v, id));
		adj[v].PB(MP(u, id));
	}

	int CountBlock() {
		for (int i = 0; i < block.size(); i++)
			vst[block[i]] = true;
		int sum = 0;
		for (int i = 0; i < block.size(); i++) {
			int u = block[i];
			for (int j = 0; j < adj[u].size(); j++) {
				if (vst[adj[u][j].first])
					sum++;
			}
		}

		sum /= 2;
		if (sum > block.size())
			ret2 += sum;
		if (sum < block.size())
			ret1 += sum;
		for (int i = 0; i < block.size(); i++)
			vst[block[i]] = false;
	}

	void Tarjan(int u) {
	    dfn[u] = low[u] = depth++;
		S.push(u);
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i].first;
			int id = adj[u][i].second;
			if (dfn[v] == -1) {
				visit[id] = true;//It's an undirected graph
				Tarjan(v);
	            low[u] = min(low[u], low[v]);
				if (low[v] >= dfn[u]) {
					block.clear();
					int x;
					do {
						x = S.top();
						S.pop();
						block.PB(x);
					}while (x != v);
					block.PB(u);
					CountBlock();
				}
	        } else if (!visit[id]) {
	            low[u] = min(low[u], dfn[v]);
	        }
	    }
	}

	void BCC() {
		depth = 0; size = 0;
		ret1 = ret2 = 0;
		while (!S.empty())
			S.pop();
		for (int i = 0; i < N; i++)
			dfn[i] = -1;
	    for (int i = 0; i < N; i++)
		    if (dfn[i] == -1) Tarjan(i);
		printf("%d %d\n", ret1, ret2);
	}

}g;

int a[MAXM], b[MAXM];
int n, m;
//Hdu3394
int main() {
	while (scanf("%d%d", &n, &m) && n + m) {
		g.init(n);
		for (int i = 0; i < m; i++) {
			scanf("%d%d", &a[i], &b[i]);
			g.addEdge(a[i], b[i], i);
		}
		g.BCC();
	}
	return 0;
}
