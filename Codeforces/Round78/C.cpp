#include <cstdio>

int dp[100][10] = {0};

int main()
{
	char str[10];
	scanf("%s", str);
	int n = strlen(len);
	for (int i = 0; i < n; i++)
	{
		for (int j = 1; j <= 6; j++)
		{
			if (i == 1) dp[str[i] - 'A'][j] = 1;
			else
			{

			}
		}
	}
}
