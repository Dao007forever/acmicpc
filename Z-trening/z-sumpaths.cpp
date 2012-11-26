/*
 * 求一棵树上两节点之间的距离恰好为M的点对数
 * f(i,j)表示以i为根，当前距离为j的点的个数，答案就是统计所有的边u<->v，ret+=f(u,j)*f(v,M-j-w)
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

typedef long long LL;
const int maxn = 50005;
const int maxm = 105;
const LL mod = 321555123LL;
int N, M;
LL ret, dp[maxn][maxm];
vector<int> adj[maxn], w[maxn];

void dfs(int u) 
{
	dp[u][0] = 1;
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i], ww = w[u][i];
		if (dp[v][0]) continue;
		dfs(v);
		for (int j = 0; j <= M; j++) 
			if (M - j - ww >= 0) {
				ret += dp[u][j] * dp[v][M - j - ww];
			}
		for (int j = M; j >= ww; j--) {
			dp[u][j] += dp[v][j - ww];
			dp[u][j] %= mod;
		}
	}
}

int main()
{
	ret = 0;
	cin >> N >> M;
	for (int i = 0; i < N - 1; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		adj[a].push_back(b); w[a].push_back(c);
		adj[b].push_back(a); w[b].push_back(c);
	}
	dfs(1);
	cout << ret << endl;
	return 0;
}

