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

const int maxn = 50005;
int n, r1, r2;
int p[maxn];
vector<int> adj[maxn];

void dfs(int u, int fa) {
	p[u] = fa;
	for (int i = 0, v; i < adj[u].size(); i++)
		if ((v = adj[u][i]) != fa) dfs(v, u);
}

int main() {
	scanf("%d%d%d", &n, &r1, &r2);
	for (int i = 1; i <= n; i++) {
		if (i != r1) {
			int x;
			scanf("%d", &x);
			adj[i].PB(x); adj[x].PB(i);
		}
	}

	dfs(r2, -1);
	for (int i = 1; i <= n; i++)
		if (i != r2) printf("%d ", p[i]);
	return 0;
}
