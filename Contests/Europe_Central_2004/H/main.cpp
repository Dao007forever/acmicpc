/*
 * Author: Yang Zhang
 * Created Time: Sun 01 Jul 2012 04:39:15 PM UTC
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

const int MAXN = 2005;
int n1, n2;
int id[1000005], t[1000005];
int mk[MAXN], cx[MAXN], cy[MAXN];
vector<int> adj[MAXN];

void addEdge(int u, int v) {
	adj[u].PB(v);
	//cout << u << "->" << v << endl;
}

int path(int u) {
	for (int i = 0, v; i < adj[u].size(); i++) {
		if (!mk[v = adj[u][i]]) {
			mk[v] = 1;
			if (cy[v] == -1 || path(cy[v])) {
				cx[u] = v;
				cy[v] = u;
				return 1;
			}
		}
	}
	return 0;
}

int MaxMatch() {
	memset(cx, -1, sizeof(cx));
	memset(cy, -1, sizeof(cy));
	int ret = 0;
	for (int i = 0; i < n1; i++) {
		if (cx[i] == -1) {
			memset(mk, 0, sizeof(mk));
			ret += path(i);
		}
	}
	return ret;
}

int main() {
	while (scanf("%d%d", &n1, &n2) && n1 && n2) {
		for (int i = 0; i <= 2000; i++)
			adj[i].clear();
		memset(id, -1, sizeof(id));
		for (int i = 0; i < n1; i++) {
			int m;
			scanf("%d", &m);
			while (m--) {
				int x, y;
				scanf("%d%d", &x, &y);
				id[x] = i; t[x] = y;
			}
		}
		for (int i = 0; i < n2; i++) {
			int m;
			scanf("%d", &m);
			while (m--) {
				int x, y;
				scanf("%d%d", &x, &y);
				if (id[x] != -1 && t[x] != y) {
					addEdge(id[x], i);
				}
			}
		}

		int ret = MaxMatch();
		printf("%d\n", ret);
	}
	return 0;
}

