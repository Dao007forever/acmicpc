/*
 * 状压dp，dp[i]表示状态为i时的最小伤害，倒序dp
 */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int inf = 1000000000;
int n;
int d[21];
int dp[1 << 21];

int main()
{
	freopen("in.txt", "r", stdin);
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> d[i];
	for (int i = 0; i < 1 << n; i++)
		dp[i] = inf;
	dp[(1 << n) - 1] = 0;
	for (int s = (1 << n) - 1; s >= 0; s--)
		if (dp[s] < inf) {
			for (int j = 0; j < n; j++) {
				int a = j - 1, b = j, c = j + 1;
				if (a == -1) a = n;
				if (c == n) c = 0;
				int x = s;
				if (x & (1 << a)) x -= (1 << a);
				if (x & (1 << b)) x -= (1 << b);
				if (x & (1 << c)) x -= (1 << c);
				if (x == s) continue;
				int sum = 0;
				for (int k = 0; k < n; k++)
					if (x & (1 << k)) sum += d[k];
				dp[x] = min(dp[x], dp[s] + sum);
			}
		}
	cout << dp[0] << endl;
	return 0;
}
