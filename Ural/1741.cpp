#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 10005
#define MAXM 10005
typedef long long LL;
const LL inf = 1LL << 45;
struct Edge {
	int v, next, w, type;
}edge[MAXM];
struct node {
	int u, type;
};
int num, Head[MAXN];
LL dist[MAXN][5];
int N, M;

void addEdge(int u, int v, int w, int type) {
	edge[num].v = v;
	edge[num].w = w;
	edge[num].type = type;
	edge[num].next = Head[u];
	Head[u] = num++;
}

int main()
{
	freopen("in.txt", "r", stdin);
	num = 0;
	memset(Head, -1, sizeof(Head));
	cin >> N >> M;
	while (M--) {
		int u, v, w, type;
		char t[10];
		scanf("%d %d %d %s", &u, &v, &w, t);
		if (*t == 'L') type = 0;
		else if (*t == 'P') type = 1;
		else type = 2;
		addEdge(u, v, w, type);
	}
	for (int i = 1; i <= N; i++) {
		dist[i][0] = dist[i][1] = inf;
	}
	dist[1][0] = 0;
	node st;
	st.u = 1; st.type = 0;
	queue<node> Q;
	Q.push(st);
	while (!Q.empty()) {
		node cur = Q.front();
		Q.pop();
		int u = cur.u;
		for (int i = Head[u]; i != -1; i = edge[i].next) {
			int v = edge[i].v, t = edge[i].type;
			LL w = (long long)edge[i].w;
			if (t == 0) {
				if (cur.type == 0) {
					if (dist[u][cur.type] + w < dist[v][0]) {
						dist[v][0] = dist[u][cur.type] + w;
						node tmp;
						tmp.u = v; tmp.type = 0;
						Q.push(tmp);
					}
				}
			} else if (t == 1) {
			   	if (dist[u][cur.type] + w < dist[v][1]) {
					dist[v][1] = dist[u][cur.type] + w;
					node tmp;
					tmp.u = v; tmp.type = 1;
					Q.push(tmp);
				}
			} else {
				if (dist[u][cur.type] + w < dist[v][cur.type]) {
					dist[v][cur.type] = dist[u][cur.type] + w;
					node tmp;
					tmp.u = v; tmp.type = cur.type;
					Q.push(tmp);
				}
			}
		}
	}
	if (dist[N][0] == inf && dist[N][1] == inf) {
		puts("Offline");
	} else {
		puts("Online");
		LL ret = min(dist[N][0], dist[N][1]);
		cout << ret << endl;
	}
	return 0;
}
