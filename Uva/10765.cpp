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


#define MAXN 10005
int n, m;
int depth;
int dfn[MAXN], low[MAXN], tag[MAXN];
vector<pair<int, int> > graph[MAXN];
bool visit[MAXN * 100];

void Tarjan(int u, int dep) {
    dfn[u] = low[u] = dep;
    for (int i = 0; i < graph[u].size(); i++) {
        int v = graph[u][i].first;
        int id = graph[u][i].second;
        if (dfn[v] == -1) {
            visit[id] = true;//It's an undirected graph
            Tarjan(v, dep + 1);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) tag[u]++;//Vertex u is a Cut-Vertex
        } else if (!visit[id]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

void FindCutVertex() {
	for (int i = 0; i < n; i++)
		dfn[i] = -1;
	for (int i = 0; i < n; i++)
		if (dfn[i] == -1) {
			Tarjan(i, 0);
			tag[i]--;//Vertex i is the root
		}
}

void addEdge(int a, int b, int id) {
	graph[a].PB(MP(b, id));
	graph[b].PB(MP(a, id));
}

int main(int argc, char const *argv[])
{
	while (~scanf("%d%d", &n, &m) && n && m) {
		int a, b;
		int M = 0;
		while (scanf("%d%d", &a, &b)) {
			if (a == -1 && b == -1) break;
			addEdge(a, b, M++);
		}
		memset(tag, 0, sizeof(tag));
		memset(visit, 0, sizeof(visit));
		FindCutVertex();
		vector<pair<int, int> > ans;
		for (int i = 0; i < n; i++) {
			ans.PB(MP(-(tag[i] + 1), i));
		}
		sort(ans.begin(), ans.end());
		for (int i = 0; i < m; i++) {
			printf("%d %d\n", ans[i].second, -ans[i].first);
		}
		puts("");
		for (int i = 0; i < n; i++) graph[i].clear();
	}
	return 0;
}