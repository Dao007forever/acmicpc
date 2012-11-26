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

#define MAXN 305
struct Graph {
	int n;
	int cx[MAXN * MAXN], cy[MAXN * MAXN], mk[MAXN * MAXN];
	vector<int> adj[MAXN * MAXN];

	void init(int n) {
		this->n = n;
		for (int i = 0; i <= n; i++)
			adj[i].clear();
	}

	void addEdge(int u, int v) {
		adj[u].PB(v);
	}

	int path(int u) {
		for (int i = 0, v; i < adj[u].size(); i++) {
			if (!mk[v = adj[u][i]]) {
				mk[v] = 1;
				if (!cy[v] || path(cy[v])) {
					cx[u] = v;
					cy[v] = u;
					return 1;
				}
			}
		}
		return 0;
	}

	int MaxMatch() {
		int ret = 0;
		memset(cx, 0, sizeof(cx));
		memset(cy, 0, sizeof(cy));
		for (int i = 1; i <= n; i++) {
			if (!cx[i]) {
				memset(mk, 0, sizeof(mk));
				ret += path(i);
			}
		}
		return ret;
	}
}g;
int n, m;
int xs[MAXN][MAXN], ys[MAXN][MAXN];
char mat[MAXN][MAXN];

void init() {
	scanf("%d%d", &n, &m);
	char ch;
	scanf("%c", &ch);
	memset(xs, 0, sizeof(xs));
	memset(ys, 0, sizeof(ys));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%c", &mat[i][j]);
			scanf("%c", &ch);
		}
	}
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		bool flag = false;
		for (int j = 0; j < m; j++) {
			if (mat[i][j] == 'H') {
				if (!flag) cnt++;
				xs[i][j] = cnt;
				flag = true;
			}
			else if (mat[i][j] == 'A') flag = false;
		}
	}
	g.init(cnt);
	cnt = 0;
	for (int j = 0; j < m; j++) {
		bool flag = false;
		for (int i = 0; i < n; i++) {
			if (mat[i][j] == 'H') {
				if (!flag) cnt++;
				ys[i][j] = cnt;
				flag = true;
			}
			else if (mat[i][j] == 'A') flag = false;
		}
	}
}

void work() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			if (xs[i][j]) g.addEdge(xs[i][j], ys[i][j]);
	}
	int ret = g.MaxMatch();
	printf("%d\n", ret);

}

int main() {
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		init();
		work();
	}
	return 0;
}
