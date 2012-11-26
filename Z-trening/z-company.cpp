/*
 * 一个公司，每个人带了一个价值为Vi的礼物，现在要求每个员工和他的直接上司不能同时参加，求最大价值
 * 树形DP, f(i,0)表示以i为根且i不参加的最大价值，f(i,1)表示以i为跟且i参加的最大价值，则f(i,0)+=max(f(son[i],0),f(son[i],1)), f(i,1)+=f(son[i],0)
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

const int maxn = 100005;
long long dp[maxn][2], v[maxn];
vector<int> adj[maxn];
int N;

void dfs(int u)
{
	dp[u][1] = v[u];
	for (int i = 0; i < adj[u].size(); i++) {
		int x = adj[u][i];
		dfs(x);
		dp[u][0] += max(dp[x][0], dp[x][1]);
		dp[u][1] += dp[x][0];
	}
}

int main()
{
//	freopen("in", "r", stdin);
	cin >> N;
	cin >> v[0];
	for (int i = 1; i < N; i++) {
		int u;
		cin >> u >> v[i];
		adj[u].push_back(i);
	}
	dfs(0);
	long long ret = max(dp[0][0], dp[0][1]);
	cout << ret << endl;
	return 0;
}
