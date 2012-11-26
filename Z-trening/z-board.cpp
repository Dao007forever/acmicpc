/*
 * R*C的方阵中，‘.’表示可走，‘#’表示不可走，每次只能向下或者向左走，分别用‘D’和‘R’表示，求从(1,1)走到(R,C)的字典序第K大的方案
 * f(i,j,k)表示走到(i,j)，上一步走的是k，0表示'D'，1表示‘R’的方案数，从(R,C)倒退出f(1,1,0)和(1,1,1)，然后求方案就从(1,1,K)顺着直到(R,C,0)，同时记录路径
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

const int maxn = 505;
const int inf = 1000000001;
int R, C, K;
char st[maxn][maxn];
long long dp[maxn][maxn][2];
vector<char> ans;

void DP()
{
	memset(dp, 0, sizeof(dp));
	if (st[R - 2][C - 1] == '.' && st[R - 1][C - 1] == '.')
		dp[R - 2][C - 1][0] = 1;
	if (st[R - 1][C - 2] == '.' && st[R - 1][C - 1] == '.')
		dp[R - 1][C - 2][1] = 1;
	for (int i = R - 1; i >= 0; i--)
		for (int j = C - 1; j >= 0; j--) 
		if (dp[i][j][0] || dp[i][j][1]) {
			if (i > 0 && st[i - 1][j] == '.') {
				dp[i - 1][j][0] += dp[i][j][0] + dp[i][j][1];
				if (dp[i - 1][j][0] > inf) dp[i - 1][j][0] = inf;
			}
			if (j > 0 && st[i][j - 1] == '.') {
				dp[i][j - 1][1] += dp[i][j][0] + dp[i][j][1];
				if (dp[i][j - 1][1] > inf) dp[i][j - 1][1] = inf;
			}
		}
}

void dfs(int x, int y, int rest)
{
	if (x > R - 1 || y > C - 1) return;
	if (x == R - 1 && y == C - 1) return;
	if (rest > dp[x][y][0]) {
		ans.push_back('R');
		dfs(x, y + 1, rest - dp[x][y][0]);
	} else {
		ans.push_back('D');
		dfs(x + 1, y, rest);
	}
}

int main()
{
//	freopen("in", "r", stdin);
	cin >> R >> C >> K;
	for (int i = 0; i < R; i++)
		scanf("%s", st[i]);
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

