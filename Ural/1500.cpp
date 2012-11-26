#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

struct Edge {
	int v, next, c;
}edge[200000];
int num, Head[33], Q[100001];
int vis[33], adj[33][33];
int K, N, M;

void addEdge(int u, int v, int c)
{
	edge[num].v = v;
	edge[num].c = c;
	edge[num].next = Head[u];
	Head[u] = num++;
}

int main()
{
	freopen("in.txt", "r", stdin);
	num = 0;
	memset(Head, -1, sizeof(Head));
	memset(adj, 0, sizeof(adj));
	cin >> K >> N >> M;
	while (M--) {
		int a, b, c;
		cin >> a >> b >> c;
		//addEdge(a, b, c);
		//addEdge(b, a, c);
		adj[a][b] = adj[a][b] | (1 << c);
		adj[b][a] = adj[a][b];
	}
	int ret = 1000000, retset;
	for (int st = (1 << K) - 1; st > 0; st--) {
		int sum = 0;
		for (int i = 0; i < K; i++) {
		    sum += (bool)(st & (1 << i));
		}
		if (sum >= ret) continue;
		//queue<int> Q;
		//Q.push(0);
		int head = 0, tail = 0;
		Q[tail++] = 0;
		memset(vis, false, sizeof(vis));
		vis[0] = true;
		int flag = false;
		while (head < tail) {
			//int u = Q.front();
			//Q.pop();
			int u = Q[head++];
			if (u == 1) {
				flag = true;
				break;
			}
			/*for (int i = Head[u]; i != -1; i = edge[i].next) {
				int v = edge[i].v, c = edge[i].c;
				if (!vis[v] && f[c]) {
					vis[v] = true;
					//Q.push(v);
					Q[tail++] = v;
				}
				}*/
			for (int i = 0; i < N; i++) {
				if (!vis[i] && adj[u][i] & st) {
					vis[i] = true;
					Q[tail++] = i;
				}
			}
		}
		if (flag) {
			ret = sum;
			retset = st;
		}
	}
	cout << ret << endl;
	for (int i = 0; i < K; i++)
		if (retset & (1 << i)) printf("%d ", i);
	return 0;
}
