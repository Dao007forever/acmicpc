#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 2222;
char txt[MAXN], a[MAXN], b[MAXN];
int s[MAXN], e[MAXN];
int dp[MAXN][MAXN], mx[MAXN];

bool is_sub(int idx, char *a)
{
	int l = strlen(a);
	for (int i = 0; i < l; i++)
		if (txt[idx + i] != a[i]) return false;
	return true;
}

int main()
{
	freopen("in", "r", stdin);
	scanf("%s%s%s", txt, a, b);
	int n = strlen(txt), la = strlen(a), lb = strlen(b);
	for (int i = 0; i <= n; i++)
	{
		if (is_sub(i, a)) s[i] = 1;
		if (is_sub(i, b)) e[i + lb - 1] = 1;
	}

	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
		{
			if (txt[i] == txt[j])
			{
				dp[i][j] = (i ? dp[i - 1][j - 1] : 0) + 1;
			}
			mx[j] = max(mx[j], dp[i][j]);
		}
	
	int ans = 0;
	for (int i = 0; i < n; i++)
		for (int len = 1; i + len - 1 < n; len++)
		{
			if (s[i] && e[i + len - 1] && len > mx[i + len - 1])
				if (i + la - 1 <= i + len - 1 && i + len - lb >= i)
					ans++;
		}
	cout << ans << endl;
	return 0;
}
