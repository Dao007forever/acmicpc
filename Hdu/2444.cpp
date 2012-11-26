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

int n, m;
int mate[222], col[222];
bool mk[222];
bool adj[222][222], odd;

void dfs(int u, int c) {
	if (odd) return;
	if (col[u] != -1) {
		if (col[u] != c) {
			odd = true;
		}
		return;
	}
	col[u] = c;
	for (int i = 0; i < n; i++)
		if (adj[u][i]) {
			dfs(i, 1 - c);
		}
}

int dfs(int u) {
	for (int v = 0; v < n; v++) {
		if (col[v] == 0) continue;
		if (adj[u][v] && !mk[v]) {
			mk[v] = true;
			if (mate[v] == -1 || dfs(mate[v])) {
				mate[v] = u;
				return 1;
			}
		}
	}
	return 0;
}

int maxMatch() {
	memset(mate, -1, sizeof(mate));
	int ret = 0;
	for (int i = 0; i < n; i++) {
		if (col[i] == 1) continue;
		memset(mk, 0, sizeof(mk));
		ret += dfs(i);
	}
	return ret;
}

int main(int argc, char const *argv[])
{
	while (~scanf("%d%d", &n, &m)) {
		memset(adj, 0, sizeof(adj));
		for (int i = 0; i < m; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			a--; b--;
			adj[a][b] = adj[b][a] = 1;
		}
		memset(col, -1, sizeof(col));
		odd = false;
		for (int i = 0; i < n; i++) {
			if (col[i] == -1) {
				dfs(i, 0);
			}
		}
		if (odd) {
			puts("No");
			continue;
		}
		int ret = maxMatch();
		printf("%d\n", ret);
	}
	return 0;
}