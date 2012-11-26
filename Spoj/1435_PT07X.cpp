/*
 * 跟Spoj666一样而且更简单，不同统计方案数
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

const int maxn = 100010;
int N;
int f[2][maxn];
vector<int> adj[maxn];

void TreeDP(int u, int fa)
{
	for (int i = 0; i < adj[u].size(); i++)
		if (adj[u][i] != fa) {
			int v = adj[u][i];
			TreeDP(v, u);
		}
	f[1][u] = f[0][u] = 0;
	for (int i = 0; i < adj[u].size(); i++) {
		if (adj[u][i] != fa) {
			int v = adj[u][i];
			if (f[0][v] < f[1][v]) {
				f[1][u] += f[0][v];
			} else {
				f[1][u] += f[1][v];
			}

			f[0][u] += f[1][v];
		}
	}
	f[1][u]++;
}

int main()
{
	cin >> N;
	if (N == 1) {
		cout << 1 << endl;
		return 0;
	}
	for (int i = 1; i < N; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	TreeDP(1, 0);
	int ret = min(f[1][1], f[0][1]);
	cout << ret << endl;
	return 0;
}

