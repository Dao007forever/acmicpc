/*
 * Author: Yang Zhang
 * Created Time: Tue 04 Sep 2012 07:08:53 PM CST
 * File Name: 10086_JMPMNKEY.cpp
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

int n, m;
int adj[25];
bool vis[1<<21];
int pre[1<<21], shot[1<<21];

bool bfs() {
	memset(vis, 0, sizeof(vis));
	queue<int> q;
	q.push((1<<n)-1);
	pre[(1<<n)-1] = -1;
	vis[(1<<n)-1] = true;
	while (!q.empty()) {
		int mask = q.front(); q.pop();
		for (int i = 0; i < n; i++)
			if (mask & (1 << i)) {
				int nxt = 0;
				for (int j = 0; j < n; j++)
					if ((mask & (1 << j)) && (j != i)) nxt |= adj[j];
				if (!vis[nxt]) {
					vis[nxt] = true;
					pre[nxt] = mask;
					shot[nxt] = i;
					q.push(nxt);
					if (nxt == 0) return true;
				}
			}
	}
	return false;
}

int len;
int ans[1000005];
void output(int mask) {
	if (pre[mask] == -1) return;
	output(pre[mask]);
	ans[len++] = shot[mask];
}

int main() {
	for (; ~scanf("%d%d", &n, &m); ) {
		if (n == 0 && m == 0) break;
		memset(adj, 0, sizeof(adj));
		for (int i = 0; i < m; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			adj[a] |= (1 << b); adj[b] |= (1 << a);
		}
		if (bfs()) {
			len = 0;
			output(0);
			printf("%d:", len);
			for (int i = 0; i < len; i++)
				printf(" %d", ans[i]);
			printf("\n");
		} else {
			printf("Impossible\n");
		}
	}
	return 0;
}

