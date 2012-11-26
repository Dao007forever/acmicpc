/*
 * 一棵树，求选择最少的点，使得每条边至少有一个端点被选择，并求这个最小值的方案数
 * 树形DP，f(1,i)表示以i为根且选择这个点的最小值，f(0,i)表示以i为根且不选择这个点的最小值，如果i要选择，则它的儿子可以选择也可以不选择，如果i不选择，那么它的每个儿子必须全部选择
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

const int maxn = 100015;
const int mod = 10007;
int N;
int f[2][maxn], cnt[2][maxn];
vector<int> adj[maxn];

void TreeDP(int u, int fa)
{
	for (int i = 0; i < adj[u].size(); i++)
		if (adj[u][i] != fa) {
			int v = adj[u][i];
			TreeDP(v, u);
		}
	f[1][u] = f[0][u] = 0;
	cnt[1][u] = cnt[0][u] = 1;
	for (int i = 0; i < adj[u].size(); i++) {
		if (adj[u][i] != fa) {
			int v = adj[u][i];
			if (f[0][v] < f[1][v]) {
				f[1][u] += f[0][v];
				cnt[1][u] = cnt[1][u] * cnt[0][v] % mod;
			} else if (f[0][v] == f[1][v]) {
				f[1][u] += f[0][v];
				cnt[1][u] = cnt[1][u] * (cnt[0][v] + cnt[1][v]) % mod;
			} else {
				f[1][u] += f[1][v];
				cnt[1][u] = cnt[1][u] * cnt[1][v] % mod;
			}

			f[0][u] += f[1][v];
			cnt[0][u] = cnt[0][u] * cnt[1][v] % mod;
		}
	}
	f[1][u]++;
}

int main()
{
	freopen("in", "r", stdin);
	int Test;
	cin >> Test;
	while (Test--) {
		cin >> N;
		if (N == 1) {
			cout << 1 << " " << 1 << endl;
			continue;
		}
		for (int i = 1; i <= N; i++)
			adj[i].clear();
		for (int i = 1; i < N; i++) {
			int u, v;
			cin >> u >> v;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}

		TreeDP(1, 0);
		int ret, ret_num;
		if (f[0][1] < f[1][1]) {
			ret = f[0][1];
			ret_num = cnt[0][1];
		} else if (f[0][1] == f[1][1]) {
			ret = f[0][1];
			ret_num = (cnt[0][1] + cnt[1][1]) % mod;
		} else {
			ret = f[1][1];
			ret_num = cnt[1][1];
		}
		cout << ret << " " << ret_num << endl;
	}
	return 0;
}
