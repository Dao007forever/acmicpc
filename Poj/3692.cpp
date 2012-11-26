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

int g, b, m;
int adj[222][222], mate[222];
bool mk[222];

int dfs(int u) {
	for (int v = 0; v < b; v++) {
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
	for (int i = 0; i < g; i++) {
		memset(mk, 0, sizeof(mk));
		ret += dfs(i);
	}
	return ret;
}

int main(int argc, char const *argv[])
{
	for (int cas = 1; ~scanf("%d%d%d", &g, &b, &m); cas++) {
		if (g == 0 && b == 0 && m == 0) break;
		printf("Case %d: ", cas);
		memset(adj, 0, sizeof(adj));
		for (int i = 0; i < g; i++) {
			for (int j = 0; j < b; j++) {
				adj[i][j] = true;
			}
		}
		for (int i = 0; i < m; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			a--; b--;
			adj[a][b] = false;
		}
		int ret = g + b - maxMatch();
		printf("%d\n", ret);
	}
	return 0;
}