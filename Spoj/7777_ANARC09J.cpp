/*
 * Author: Yang Zhang
 * Created Time: Wed 22 Aug 2012 01:51:54 PM CST
 * File Name: 7777_ANARC09J.cpp
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

#define maxn 2505
int mk[maxn], cx[maxn], cy[maxn];
vector<int> adj[maxn];
int dx[] = {-1, -2, -2, -1, 1, 2, 2, 1, -1, 0, 1, 0};
int dy[] = {-2, -1, 1, 2, 2, 1, -1, -2, 0, 1, 0, -1};
int r, c;
int a[55][55];

void addEdge(int u, int v) {
	adj[u].PB(v);
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
	for (int i = 0; i < r * c; i++) {
		if (cx[i] == -1) {
			memset(mk, 0, sizeof(mk));
			ret += path(i);
		}
	}
	return ret;
}
int ID(int x, int y) {
	return x * c + y;
}
int main() {
	for (int cas = 1; scanf("%d%d", &r, &c); cas++) {
		if (r == 0 && c == 0) break;
		printf("%d. ", cas);
		for (int i = 0; i < r * c; i++)
			adj[i].clear();
		for (int i = 0; i < r; i++)
			for (int j = 0; j < c; j++)
				scanf("%d", &a[i][j]);
		for (int i = 0; i < r; i++)
			for (int j = 0; j < c; j++) {
				if (a[i][j] == -1) continue;
				for (int k = 0; k < 12; k++)
					if (a[i][j] & (1 << k)) {
						int x = i + dx[k], y = j + dy[k];
						if (x >= 0 && x < r && y >= 0 && y < c) {
							if (a[x][y] != -1) {
								if ((i + j) % 2 == 0) {
									addEdge(ID(i, j), ID(x, y));
								} else {
									addEdge(ID(x, y), ID(i, j));
								}
							}
						}
					}
			}
		int ret = MaxMatch();
		printf("%d\n", ret);
	}
	return 0;
}

