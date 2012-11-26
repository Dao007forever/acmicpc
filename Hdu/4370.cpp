/*
 * Author: Yang Zhang
 * Created Time: Thu 16 Aug 2012 03:44:16 PM UTC
 * File Name: main.cpp
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
#define maxn 305
#define maxm 90005
const int inf = 1 << 30;
struct Edge {
	int v, next, w;
};
struct Graph {

	int N, M;
	Edge edge[maxm * 2];
	int num, Head[maxn];
	int vis[maxn];
	int dis[maxn];
	int cur;

	Graph() {}

	void init(int N) {
		this->N = N;
		num = 0;
		memset(Head, -1, sizeof(Head));
	}

	void addEdge(int u, int v, int w) {
		edge[num].v = v;
		edge[num].w = w;
		edge[num].next = Head[u];
		Head[u] = num++;
	}

	void SPFA(int st) {
		queue<int> Q;
		for (int i = 1; i <= N; i++)
			dis[i] = inf, vis[i] = false;
		/*for (int i = Head[st]; i != -1; i = edge[i].next) {
			if (edge[i].v == st) continue;
			dis[edge[i].v] = edge[i].w;
			vis[edge[i].v] = true;
			Q.push(edge[i].v);
		}*/
		dis[st] = 0;
		Q.push(st);
		cur = inf;
		while (!Q.empty()) {
			int u = Q.front();
			Q.pop();
			vis[u] = false;
			for (int i = Head[u]; i != -1; i = edge[i].next) {
				int v = edge[i].v;
				if (v == st && u != st) {
					cur = min(cur, dis[u] + edge[i].w);
					continue;
				}
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
}g;

int n;
int main() {
	while (~scanf("%d", &n)) {
		g.init(n);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++) {
				int x;
				scanf("%d", &x);
				g.addEdge(i, j, x);
			}
		g.SPFA(1);
		int ret = g.dis[n];
		int r1 = g.cur;
//		int r1 = g.dis[1];
		g.SPFA(n);
		int r2 = g.cur;
//		int r2 = g.dis[n];
		ret = min(ret, r1 + r2);
		printf("%d\n", ret);
	}
	return 0;
}


