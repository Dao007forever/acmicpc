/*
 * AC
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

int N, K, T;
char R;
int adj[4][2] = {{2, 1}, {3, 0}, {0, 3}, {1, 2}};
long long dp[55][5][3];
vector<int> ans;

void DP()
{
	dp[N - 1][adj[T][0]][0] = dp[N - 1][adj[T][1]][1] = 1;
	for (int i = N - 1; i >= 1; i--)
		for (int j = 0; j < 4; j++)
			for (int k = 0; k < 2; k++) {
				dp[i - 1][adj[j][k]][k] += dp[i][j][0] + dp[i][j][1];
			}
}

void dfs(int n, int cur, int rest)
{
	if (n == N) return;
	if (rest > dp[n][cur][0]) {
		ans.push_back(1);
		dfs(n + 1, adj[cur][1], rest - dp[n][cur][0]);
	} else {
		ans.push_back(0);
		dfs(n + 1, adj[cur][0], rest);
	}
}

int main()
{
//	freopen("in", "r", stdin);
	scanf("%c %d %d", &R, &N, &K);
	T = R - 'A';
	DP();
	if (dp[0][0][0] + dp[0][0][1] < K) {
		cout << "impossible" << endl;
		return 0;
	}
	dfs(0, 0, K);
	for (int i = 0; i < ans.size(); i++)
		cout << ans[i];
	cout << endl;
	return 0;
}
