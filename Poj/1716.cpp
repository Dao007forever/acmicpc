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

const int maxn = 10005;
const int maxm = 4 * maxn;
const int inf = 1000000000;
struct Edge {
	int v, next, w;
}edge[maxm];
int num, Head[maxn];
int N, n;
int dis[maxn], vis[maxn];

void addEdge(int u, int v, int w)
{
	edge[num].v = v;
	edge[num].w = w;
	edge[num].next = Head[u];
	Head[u] = num++;
}

void spfa(int s)
{
	for (int i = 0; i <= n; i++)
		dis[i] = inf;
	dis[s] = 0;
	memset(vis, 0, sizeof(vis));
	vis[s] = 1;
	queue<int> Q;
	Q.push(s);
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		vis[u] = false;
		for (int i = Head[u]; i != -1; i = edge[i].next) {
			int v = edge[i].v;
			if (dis[u] + edge[i].w < dis[v]) {
				dis[v] = dis[u] + edge[i].w;
				if (!vis[v]) {
					vis[v] = true;
					Q.push(v);
				}
			}
		}
	}
}

int main()
{
	num = 0;
	memset(Head, -1, sizeof(Head));
	cin >> N;
	n = -1;
	for (int i = 0; i < N; i++) {
		int a, b;
		cin >> a >> b;
		n = max(n, b + 1);
		addEdge(b + 1, a, -2);
	}
	for (int i = 0; i < n; i++) {
		addEdge(i, i + 1, 1);
		addEdge(i + 1, i, 0);
	}
	int source = n + 1;
	for (int i = 0; i <= n; i++)
		addEdge(source, i, 0);
	spfa(source);
	cout << dis[n] - dis[0]<< endl;
	return 0;
}
