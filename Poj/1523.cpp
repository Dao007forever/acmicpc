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

#define MAXN 1024
int N, M;
bool visit[MAXN * 100];
vector<pair<int, int> > graph[MAXN];
int dfn[MAXN], low[MAXN], tag[MAXN];

void Tarjan(int fa, int u, int dep) {
    dfn[u] = low[u] = dep;
    for (int i = 0; i < graph[u].size(); i++) {
        int v = graph[u][i].first;
        int id = graph[u][i].second;
        if (dfn[v] == -1) {
            visit[id] = true;//It's an undirected graph
            Tarjan(u, v, dep + 1);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) tag[u]++;//Vertex u is a Cut-Vertex
        } else if (!visit[id]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

void FindCutVertex() {
	for (int i = 0; i < N; i++)
		dfn[i] = -1;
	for (int i = 0; i < N; i++)
		if (dfn[i] == -1) {
			Tarjan(-1, i, 0);
			tag[i]--;//Vertex i is the root
		}
}

int main() {
	freopen("in", "r", stdin);
	int T = 0, v1, v2;
	while (scanf("%d", &v1) != EOF && v1) {
		scanf("%d", &v2);
		v1--; v2--;
		N = M = 0;
		N = max(N, v1); N = max(N, v2);
		for (int i = 0; i < MAXN; i++)
			if (SZ(graph[i]) > 0) graph[i].clear();
		memset(tag, 0, sizeof(tag));
		memset(low, 0, sizeof(low));
		memset(visit, 0, sizeof(visit));
		graph[v1].PB(MP(v2, M));
		graph[v2].PB(MP(v1, M));
		while (scanf("%d", &v1) && v1) {
			scanf("%d", &v2);
			M++;
			v1--; v2--;
			N = max(N, v1); N = max(N, v2);
			graph[v1].PB(MP(v2, M));
			graph[v2].PB(MP(v1, M));
		}
		N++;
		FindCutVertex();
		T++;
		if (T > 1) printf("\n");
		printf("Network #%d\n", T);
		bool ok = true;
		for (int i = 0; i < N; i++)
			if (tag[i] > 0) {
				printf("  SPF node %d leaves %d subnets\n", i + 1, tag[i] + 1);
				ok = false;
			}
		if (ok) printf("  No SPF nodes\n");
	}
	return 0;
}
