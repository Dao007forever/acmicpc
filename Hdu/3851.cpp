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

const int MAXN = 1000000 + 10;
struct DAY
{
	long long D, N;
}dt[MAXN];
int T, N;
long long t, PD, PN, dp[MAXN], dat[MAXN];

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &T);
	for (int cas = 1; cas <= T; cas++)
	{
		cin >> N;
		cin >> t >> PD >> PN;
		long long sum = 0, st = 0;
		for (int i = 1; i <= N; i++)
		{
			cin >> dt[i].D >> dt[i].N;

			if (dt[i].D >= 2 * t)
			{
				int x = (dt[i].D - t) / t;
				sum += x * PD;
				dt[i].D -= x * t;
			}
			for (int k = 1; k <= dt[i].D; k++)
				dat[++st] = PD;

			if (dt[i].N >= 2 * t)
			{
				int x = (dt[i].N - t) / t;
				sum += x * PN;
				dt[i].N -= x * t;
			}
			for (int k = 1; k <= dt[i].N; k++)
				dat[++st] = PN;
		}

		int n = (int)st;
		memset(dp, 0, sizeof(dp));
		for (int i = n; i >= 1; i--)
			dp[i] = max(dp[i + 1], dp[i + t] + dat[i]);
		cout << "Case " << cas << ": " << dp[1] + sum << endl;
	}
	return 0;
}
