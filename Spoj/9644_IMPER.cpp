/*
 * Author: Yang Zhang
 * Created Time: Wed 05 Sep 2012 08:27:05 PM CST
 * File Name: 9644_IMPER.cpp
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

#define MAXN 10005
int n;
int d[MAXN];
vector<int> adj[MAXN];

void bfs(int st, int &ed) {
	for (int i = 1; i <= n; i++) d[i] = MAXN;
	d[st] = 0;
	queue<int> q;
	q.push(st);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = 0, v; i < adj[u].size(); i++)
			if (d[u] + 1 < d[v = adj[u][i]]) {
				d[v] = d[u] + 1;
				q.push(v);
			}
	}
	ed = 1;
	for (int i = 1; i <= n; i++)
		if (d[i] > d[ed]) {
			ed = i;
		}
}

int main() {
	while (scanf("%d", &n) && n != -1) {
		for (int i = 1; i <= n; i++) adj[i].clear();
		for (int i = 2; i <= n; i++) {
			int fa;
			scanf("%d", &fa);
			adj[i].PB(fa); adj[fa].PB(i);
		}
		if (n == 2) {
			puts("1");
			continue;
		}
		int far, farst;
		bfs(1, far);
		bfs(far, farst);
		printf("%d\n", (d[farst] + 1) / 2);
	}
	return 0;
}

