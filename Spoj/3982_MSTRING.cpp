#include <cstdio>
#include <cstring>

char s1[1111], s2[1111];
int dp[1111][1111], next1[1111][33], next2[1111][33];
int hash[33];
int n, m;

void update(int &a, int b)
{
	if (!a) a = b;
	else a = a < b ? a : b;
}

void solve()
{
	int ans = n;
	memset(hash, 0, sizeof(hash));
	for (int i = 0; i < n; i++)
	if (!hash[s1[i] - 'a'])
	{
		hash[s1[i] - 'a'] = 1;
		bool flag = true;
		for (int j = 0; j < m; j++)
		if (s1[i] == s2[j])
		{
			dp[i][j] = 1;
			flag = false;
			break;
		}
		if (flag)
		{
			printf("1\n");
			return;
		}
	}
	for (int i = 0; i < n; i++)
	for (int j = 0; j < m; j++)
	if (dp[i][j] && dp[i][j] + 1 < ans)
		for (int k = 0; k < 26; k++)
			if (next1[i][k])
			{
				if (!next2[j][k]) ans = dp[i][j] + 1;
				else update(dp[next1[i][k]][next2[j][k]], dp[i][j] + 1);
			}
	printf("%d\n", ans);
}

int main()
{
	freopen("in", "r", stdin);
	scanf("%s%s", s1, s2);
	memset(hash, 0, sizeof(hash));
	n = strlen(s1);
	for (int i = n - 1; i >= 0; i--)
	{
		for (int j = 0; j < 26; j++)
			next1[i][j] = hash[j];
		hash[s1[i] - 'a'] = i;
	}
	memset(hash, 0, sizeof(hash));
	m = strlen(s2);
	for (int i = m - 1; i >= 0; i--)
	{
		for (int j = 0; j < 26; j++)
			next2[i][j] = hash[j];
		hash[s2[i] - 'a'] = i;
	}
	solve();
	return 0;
}
