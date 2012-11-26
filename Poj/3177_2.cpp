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

/*
 * Find BCC, size is the number of bcc, if id[u]=id[v], it means u and v are in the same bcc
 */
const int maxn = 5005;
vector<pair<int, int> > graph[maxn];
int dfn[maxn], low[maxn], id[maxn], deg[maxn];
bool visit[maxn];
int N, M, size;
stack<int> S;

void Tarjan(int u, int dep) {
    dfn[u] = low[u] = dep;
	S.push(u);
    for (int i = 0; i < graph[u].size(); i++) {
        int v = graph[u][i].first;
        int id = graph[u][i].second;
        if (dfn[v] == -1) {
            visit[id] = true;//It's an undirected graph
            Tarjan(v, dep + 1);
            low[u] = min(low[u], low[v]);
        } else if (!visit[id]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
	if (low[u] == dfn[u]) {
		size++;
		int v;
		do {
			v = S.top();
			S.pop();
			id[v] = size;
		} while (u != v);
	}
}

void BCC() {
	while (!S.empty())
		S.pop();
	memset(id, -1, sizeof(id));
    for (int i = 0; i < N; i++)
        dfn[i] = -1;
    for (int i = 0; i < N; i++)
        if (dfn[i] == -1) Tarjan(i, 0);
}

int main() {
	freopen("in", "r", stdin);
	while (scanf("%d%d", &N, &M) != EOF) {
		memset(low, 0, sizeof(low));
		memset(visit, 0, sizeof(visit));
		size = 0;
		for (int i = 0; i < M; i++) {
			int u, v;
			scanf("%d%d", &u, &v);
			u--; v--;
			graph[u].PB(MP(v, i));
			graph[v].PB(MP(u, i));
		}
		BCC();
		for (int u = 0; u < N; u++)
			for (int i = 0; i < SZ(graph[u]); i++) {
				int v = graph[u][i].first;
				if (id[u] != id[v])
					deg[id[v]]++;
			}
		int ret = 0;
		for (int i = 1; i <= size; i++)
			if (deg[i] == 1) ret++;
		cout << (ret + 1) / 2 << endl;
	}
	return 0;
}
