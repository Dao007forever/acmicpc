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

const long long P = 1000000007;
int T;
long long dp[30];
char s[100001];
long long res;

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &T);
	while (T--)
	{
		memset(dp, 0, sizeof(dp));
		scanf("%s", s);
		res = 2;
		dp[s[0] - 'A'] = 1;
		int n = strlen(s);

		for (int i = 1; i < n; i++)
		{
			int j = s[i] - 'A';
			long long temp = (res - dp[j] + P) % P;
			res = (res + temp) % P;
			dp[j] = (dp[j] + temp) % P;
		}
		cout << res << endl;
	}
	return 0;
}
