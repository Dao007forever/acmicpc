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

const int mod = 1000000009;
const int maxn = 10005;
int n;
int dp[maxn][11][11];

bool check(int a, int b, int c) {
	int t = a * 100 + b * 10 + c;
	for (int i = 2; i * i <= t; i++)
		if (t % i == 0) return false;
	return true;
}

int main()
{
	cin >> n;
	memset(dp, 0, sizeof(dp));
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			dp[2][i][j] = 1;
	for (int i = 3; i <= n; i++)
		for (int j = 0; j < 10; j++)
			for (int k = 0; k < 10; k++)
				for (int cur = 0; cur < 10; cur++)
					if (j && check(j, k, cur)) {
						dp[i][k][cur] += dp[i - 1][j][k];
						dp[i][k][cur] %= mod;
					}
	int ret = 0;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++) {
			ret += dp[n][i][j];
			ret %= mod;
		}
	cout << ret << endl;
	return 0;
}
