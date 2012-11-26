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

#define MAXN 50005
#define MAXK 505
typedef long long LL;
LL ret, dp[MAXN][MAXK];
vector<int> adj[MAXN], w[MAXN];
int N, K;

void dfs(int u, int fa)
{
	dp[u][0] = 1;
	for (int i= 0; i < adj[u].size(); i++)
		if (adj[u][i] != fa) {
			int v = adj[u][i];
			dfs(v, u);
			for (int j = 0; j <= K; j++)
				ret += dp[u][j] * dp[v][K - j - 1];
			for (int j = K; j >= 1; j--)
				dp[u][j] += dp[v][j - 1];
		}
}

int main()
{
    freopen("in.txt", "r", stdin);
	cin >> N >> K;
	for (int i = 0; i < N - 1; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs(1, 0);
	cout << ret << endl;
	return 0;
}
