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
#define fi first
#define se second
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;

#define MAXN 105
const int inf = 0x3f3f3f3f;
struct Edge {
	int v, next;
	int b, e, c;
}edge[2005];
int E;
int Head[MAXN];
int n, m, s, t;
int dis[MAXN];
bool vis[MAXN];

void addEdge(int u, int v, int b, int e, int c) {
	edge[E].v = v; edge[E].b = b; edge[E].e = e; edge[E].c = c; edge[E].next = Head[u]; Head[u] = E++;
}

int dijkstra(int st, int time) {
	for (int i = 0; i < n; i++) {
		dis[i] = inf, vis[i] = false;
	}
	dis[st] = time;
	priority_queue<pair<int, int> > pq;
	pq.push(MP(-time, st));
	while (!pq.empty()) {
		int u = pq.top().second;
		int cur = -pq.top().first;
		pq.pop();
		vis[u] = true;
		if (u == t) return dis[t] - time;
		for (int i = Head[u]; ~i; i = edge[i].next) {
			int v = edge[i].v, b = edge[i].b, e = edge[i].e, c = edge[i].c;
			if (vis[v]) continue;
			int tmp = max(b, dis[u]) + c;
			if (e < tmp) continue;
			if (tmp < dis[v]) {
				dis[v] = tmp;
				pq.push(MP(-dis[v], v));
			}
		}
	}
	return -1;
}

int main(int argc, char const *argv[])
{
	while (~scanf("%d%d%d%d", &n, &m, &s, &t)) {
		s--; t--;
		E = 0;
		memset(Head, -1, sizeof(Head));
		int Min = inf, Max = -1;
		for (int i = 0; i < m; i++) {
			int u, v;
			int b, e, c;
			scanf("%d%d%d%d%d", &u, &v, &b, &e, &c);
			u--; v--;
			if (u == s) {
				Min = min(Min, b);
				Max = max(Max, e);
			}
			if (e - b >= c) {
				addEdge(u, v, b, e, c);
			}
		}
		int ret = inf;
		for (int i = Min; i <= Max; i++) {
			int tmp = dijkstra(s, i);
			if (tmp == -1) break;
			ret = min(ret, tmp);
		}
		if (ret == inf) {
			puts("Impossible");
		} else {
			printf("%d\n", ret);
		}
	}
	return 0;
}